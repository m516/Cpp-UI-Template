#include "app.hpp"

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


}