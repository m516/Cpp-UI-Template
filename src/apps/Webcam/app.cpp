#include "app.hpp"



#include <imgui/imgui.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <csignal>
#include <cstdio>


#include "ui/ui_utils.hpp"





namespace Apps{

void Webcam::processOnce(){
    if(!_camera.isOpened()){
        std::cout << "Error: camera isn't opened. Stopping" << std::endl;
        stopProcessingContinually();
        return;
    }
    _camera >>process_out;
    if(process_out.empty()){
        std::cout << "Warning: frame emptyu" << std::endl;
        stopProcessingContinually();
    }
}

void Webcam::uiInit(){
    App::uiInit();
    _frameViewer = MatViewer("Webcam", process_out);
    // Start the camera
    _camera.open(0, cv::CAP_ANY);
    _camera.set(cv::CAP_PROP_FRAME_WIDTH,640); // TODO temporary since I'm testing with a crummy camera
    _camera.set(cv::CAP_PROP_FRAME_HEIGHT,480);
    // Start the capture process
    startProcessingContinuallyInNewThread();
} // End Webcam::uiInit

void Webcam::uiDraw(){ 
    App::uiDraw();   
    if(!ImGui::Begin("Webcam", NULL)){
        ImGui::End();
        return;
    }
    if(_camera.isOpened()){
        if(process_out.empty()){
            ImGui::Text("Warning: frame is empty");
        }
        else{
            _frameViewer.update();
            _frameViewer.addToGUI();
            _drawControls();
        }
    }
    else{
        ImGui::Text("Cannot connect to a webcam.") ; 
        if(keepGoing()) {
            ImGui::Text("The capture thread is still running though :/");
        }
        else {
            ImGui::Text("The capture thread has stopped.");
            if(ImGui::Button("Retry?")){
                startProcessingContinuallyInNewThread();
            }
        }
    } 
    imguiScrollWhenDraggingOnVoid();
    ImGui::End();
} // End FLIR_Camera_Viewer::uiDraw

void Webcam::uiClose(){
    App::uiClose();
    stopProcessingContinually();
    _camera.release();
} // End FLIR_Camera_Viewer::uiClose



void Webcam::_drawControls(){


    static ImGuiTableFlags flags = ImGuiTableFlags_ScrollY | ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable;
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    ImVec2 outer_size = ImVec2(0.0f, TEXT_BASE_HEIGHT * 12);
    if (ImGui::BeginTable("table_scrolly", 2, flags, outer_size))
    {
        ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
        ImGui::TableSetupColumn("Property", ImGuiTableColumnFlags_None);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_None);
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();

        // FPS
        #define PRINT_PROPERTY(property){      \
            ImGui::TableSetColumnIndex(0);     \
            ImGui::Text("%s",  #property);     \
            ImGui::TableSetColumnIndex(1);     \
            ImGui::Text("%lf", _camera.get(property));     \
            ImGui::TableNextRow();             \
        }
        PRINT_PROPERTY(cv::CAP_PROP_POS_FRAMES);
        PRINT_PROPERTY(cv::CAP_PROP_FRAME_WIDTH );
        PRINT_PROPERTY(cv::CAP_PROP_FRAME_HEIGHT );
        PRINT_PROPERTY(cv::CAP_PROP_FPS );
        PRINT_PROPERTY(cv::CAP_PROP_BRIGHTNESS );
        PRINT_PROPERTY(cv::CAP_PROP_CONTRAST );
        PRINT_PROPERTY(cv::CAP_PROP_SATURATION );
        PRINT_PROPERTY(cv::CAP_PROP_HUE );
        PRINT_PROPERTY(cv::CAP_PROP_BACKEND );
        #undef PRINT_PROPERTY


        ImGui::EndTable();
    

    }
    
    

    ImGui::Text("Resolution");
    static int resolution = 0;
    if(ImGui::RadioButton("full", &resolution, 0)){
        int w = (int) _camera.get(cv::CAP_PROP_FRAME_WIDTH);
        int h = (int) _camera.get(cv::CAP_PROP_FRAME_HEIGHT);
        std::cout << "Width: " << w << "\t Height: " << h << std::endl;
        _camera.set(cv::CAP_PROP_FRAME_WIDTH,w);
        _camera.set(cv::CAP_PROP_FRAME_HEIGHT,h);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("640x480", &resolution, 1)){
        _camera.set(cv::CAP_PROP_FRAME_WIDTH,640);
        _camera.set(cv::CAP_PROP_FRAME_HEIGHT,480);
    }
    ImGui::SameLine();
    if(ImGui::RadioButton("1280x720", &resolution, 2)){
        _camera.set(cv::CAP_PROP_FRAME_WIDTH,1280);
        _camera.set(cv::CAP_PROP_FRAME_HEIGHT,720);
    }
} // end _drawControls



} // End namspace Apps