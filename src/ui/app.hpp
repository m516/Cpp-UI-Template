#pragma once

#include <vector>
#include <memory>

namespace app{

    // A class that represents a virtual window.
    // Doesn't do anything by itself; but is capable of turning a class into an app with a GUI
    class App{
        public:
        typedef std::shared_ptr<App> Ptr;
        App();
        ~App();

        // Called by the UI when the graphics are being initialized. Don't draw anything here!
        virtual void uiInit();
        // Called by the UI when the user wishes to close the app
        virtual void uiClose();
        // Called by the UI once every frame. Use ImGUI windows and widgets here. 
        virtual void uiDraw(){};

        protected:
        void imguiScrollWhenDraggingOnVoid();

        private:
        // This window ID
        size_t _id = 0;
        bool _ui_init = false;

    };

    
    extern std::vector<App::Ptr> list;
}