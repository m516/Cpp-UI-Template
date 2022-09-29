#include "app.hpp"

#include "imgui/imgui_internal.h"


namespace app{
    std::vector<App::Ptr> list;

    void App::uiInit(){
        if(_ui_init) return;

        list.push_back(Ptr(this));
        _id = list.size()-1;
        _ui_init = true;
    }

    
    void App::uiClose(){
        if(!_ui_init) return;

        size_t id = _id;
        list.erase(list.begin() + id);
        for(int i = id; i < list.size(); i++){
            list[i]->_id -= 1;
        }
        _ui_init = false;
    }

    App::App(){
    }

    App::~App(){
    }

    void App::imguiScrollWhenDraggingOnVoid()
    {
        ImVec2 delta = ImGui::GetIO().MouseDelta;
        delta.x = -delta.x; delta.y = -delta.y;
        ImGuiContext& g = *ImGui::GetCurrentContext();
        ImGuiWindow* window = g.CurrentWindow;
        bool hovered = false;
        bool held = false;
        ImGuiButtonFlags button_flags = ImGuiButtonFlags_MouseButtonLeft;
        if (g.HoveredId == 0) // If nothing hovered so far in the frame (not same as IsAnyItemHovered()!)
            ImGui::ButtonBehavior(window->Rect(), window->GetID("##scrolldraggingoverlay"), &hovered, &held, button_flags);
        if(ImGui::IsMouseClicked(0)) return;
        if (held && delta.x != 0.0f)
            ImGui::SetScrollX(window, window->Scroll.x + delta.x);
        if (held && delta.y != 0.0f)
            ImGui::SetScrollY(window, window->Scroll.y + delta.y);
        }


}