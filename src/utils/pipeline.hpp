#pragma once

#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#include <exception>

namespace Pipeline
{



template<typename InType, typename OutType>
class Process{
    public:

    
    InType *process_in = NULL;
    OutType process_out;

    Process(){}
    
    // Connect to the pipeline
    template<typename super_inType>
    Process(Process<super_inType, InType> &input)
    {
        _cv_in = &(input._cv_out);
        process_in = &(input.process_out);
        _input_mutex = &(input._my_mutex);
        _parent_keep_going = &(input._keep_going);

    }

    ~Process(){
        stopProcessingContinually();
        if(_thread != nullptr) delete _thread;
    }


    // This method is run once every time 
    virtual void processOnce(){}

    // Keeps processing the data when it's available
    void processContinually(){
        _keep_going = true;
        while(_keep_going){
            // Stop if there's no more data to process
            if(_parent_keep_going && !*_parent_keep_going) {
                std::cout << "Parent stopped going" << std::endl;
                _keep_going = false;
                return;
            }
            // Wait for new data to come in
            if(_input_mutex) {
                std::unique_lock<std::mutex> lock_in(*_input_mutex);
                _cv_in->wait(lock_in);
                // Process it
                processOnce_s();
                lock_in.unlock();
            }
            else{
                processOnce_s();
            } // End if
            // Let the next processs in the pipeline use it
            _cv_out.notify_all();
        } // End while
        
        std::cout << "I stopped going" << std::endl;
    } // End processContinually

    void startProcessingContinuallyInNewThread(){
        if(_thread != nullptr) delete _thread;
        if(_keep_going) return;
        _keep_going = true;
        _thread = new std::thread(&Process::processContinually, this);
    }

    void stopProcessingContinually(){
        _keep_going = false;
        _cv_out.notify_all();
        if(_thread != nullptr){
            if(std::this_thread::get_id() != _thread->get_id()) _thread->join();
        }
    }

    bool keepGoing(){return _keep_going;}

    public:


    // Unlocked every time I have new data.
    std::mutex _my_mutex;
    // Unlocked every time there's new data for me.
    // It's my job to lock this mutex when I'm done,
    // and I do that in processContinually.
    std::mutex *_input_mutex = NULL;

    // Set to false to stop the pipeline safely
    bool _keep_going = false;
    // A pointer to the parent's "_keep_going" if it exists
    bool *_parent_keep_going = NULL;

    std::condition_variable *_cv_in;
    std::condition_variable _cv_out;

    // The thread where the processing is done
    std::thread *_thread = nullptr;
    std::exception_ptr thread_exception = nullptr;
    // Returns true if the Process has been aborted
    bool process_aborted(){return thread_exception!=nullptr;}
    // ProcessOnce(), only safe
    void processOnce_s(){
        try{
            processOnce();
        }
        catch(std::exception e){ // Fail gracefully
            std::cerr << "Pipeline process failed with exception: " << e.what() << std::endl;
            thread_exception = std::current_exception();
            stopProcessingContinually();
        }
    }

}; // end class Process

} // end namespace Pipeline
