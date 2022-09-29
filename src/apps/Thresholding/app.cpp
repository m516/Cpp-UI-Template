#include "app.hpp"



#include <imgui/imgui.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <csignal>
#include <cstdio>


#include "ui/ui_utils.hpp"





namespace Apps{

void Thresholding::processOnce(){
    static int i = 0;
    cv::Mat o = cv::Mat::zeros(process_in->rows, process_in->cols, CV_8UC3);
    cv::Mat mask;
    cv::inRange(
        *process_in, 
        cv::Scalar(lowColor[2]*256, lowColor[1]*256, lowColor[0]*256), 
        cv::Scalar(highColor[2]*256, highColor[1]*256, highColor[0]*256),
        mask
    );
    process_in->copyTo(o, mask);

    o.copyTo(process_out);
    //process_in->copyTo(process_out); // TODO
} // End Thresholding::processOnce

void Thresholding::uiInit(){
    App::uiInit();
    // Initialize the image viewer
    _frameViewer = MatViewer("Thresholding", process_out);
    // Start the capture process
    startProcessingContinuallyInNewThread();
} // End Thresholding::uiInit

void Thresholding::uiDraw(){ 
    App::uiDraw();   
    // Rendering shortcut
    if(!ImGui::Begin("Thresholding", NULL)){
        ImGui::End();
        return;
    }
    //if(ImGui::CollapsingHeader("CollapsingHeader")){ // TODO collapse headers
        _frameViewer.update();
        _frameViewer.addToGUI();
    //}

    _drawControls();
    imguiScrollWhenDraggingOnVoid();
    ImGui::End();
} // End Thresholding::uiDraw

void Thresholding::uiClose(){
    App::uiClose();
} // End Thresholding::uiClose



void Thresholding::_drawControls(){
    ImGui::ColorEdit3("Low color", lowColor);
    ImGui::ColorEdit3("High color", highColor);
} // end _drawControls



} // End namspace Apps