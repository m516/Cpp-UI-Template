#pragma once

#include "ui/app.hpp"
#include "utils/pipeline.hpp"
#include <opencv2/core.hpp>
#include "graphics/mat_viewer.hpp"
#include <thread>

namespace Apps{

// Realtime, multithreaded thresholding with a UI
class Thresholding: public app::App, public Pipeline::Process<cv::Mat, cv::Mat>{
    public:


    template<typename super_inType>
    Thresholding(Pipeline::Process<super_inType, cv::Mat> &input)
    : app::App(), Pipeline::Process<cv::Mat, cv::Mat>(input)
    {
    }

    virtual void uiInit();

    virtual void uiDraw();

    virtual void uiClose();

    // Inherited from Process
    virtual void processOnce();
    
    private:
        MatViewer _frameViewer;
        void _drawControls();

        float lowColor[3], highColor[3];

}; // End class Webcam




} // End namespace Apps