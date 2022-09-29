#pragma once

#include "ui/app.hpp"
#include "utils/pipeline.hpp"
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include "graphics/mat_viewer.hpp"
#include <thread>

namespace Apps{


class Webcam: public app::App, public Pipeline::Process<int, cv::Mat>{
    public:

    virtual void uiInit();

    virtual void uiDraw();

    virtual void uiClose();

    // Inherited from Process
    virtual void processOnce();
    
    private:
        MatViewer _frameViewer;
        cv::VideoCapture _camera;
        void _drawControls();

}; // End class Webcam




} // End namespace Apps