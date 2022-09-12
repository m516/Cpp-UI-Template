#pragma once

#include "ui/app.hpp"

#include <imgui/imgui.h>


namespace Apps{


class ImGui_Demo: public app::App{
    public:

    virtual void uiDraw(){
        ImGui::ShowDemoWindow(NULL);
    }

}; // End class ImGui_Demo


} // End namespace Apps