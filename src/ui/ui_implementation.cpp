
#include "ui.hpp"

#include <iostream>
#include <thread>
#include <exception>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "ui/app.hpp"




/////////////////////////////////////////// Globals  //////////////////////////////////////////
namespace UI{

namespace Window{
    GLFWwindow* window;
    int width, height;
    ImVec4 background_color(0.45f, 0.55f, 0.60f, 0.00f);
    ImFont* font;
}





/////////////////////////////////////////// Utilities  ////////////////////////////////////////

/**
 * A callback function for GLFW to execute when an internal error occurs with the
 * library.
 */
void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


void setStyle(){
    // Fonts
    ImGuiIO& io = ImGui::GetIO();
    Window::font = io.Fonts->AddFontFromFileTTF("/usr/share/fonts/truetype/noto/NotoMono-Regular.ttf", 18.f);

    // Colors
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.13f, 0.26f, 0.42f, 0.92f);
    colors[ImGuiCol_Border]                 = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.08f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.27f, 0.28f, 0.29f, 1.00f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_Button]                 = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
    colors[ImGuiCol_Separator]              = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.14f, 0.15f, 0.18f, 0.52f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_DockingPreview]         = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
    colors[ImGuiCol_NavHighlight]           = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.00f, 0.49f, 1.00f, 0.36f);



    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowPadding                     = ImVec2(8.00f, 8.00f);
    style.FramePadding                      = ImVec2(10.00f, 10.00f);
    style.CellPadding                       = ImVec2(6.00f, 6.00f);
    style.ItemSpacing                       = ImVec2(20.00f, 8.00f);
    style.ItemInnerSpacing                  = ImVec2(10.00f, 4.00f);
    style.TouchExtraPadding                 = ImVec2(6.00f, 6.00f);
    style.IndentSpacing                     = 16;
    style.ScrollbarSize                     = 32;
    style.GrabMinSize                       = 20;
    style.WindowBorderSize                  = 1;
    style.ChildBorderSize                   = 1;
    style.PopupBorderSize                   = 1;
    style.FrameBorderSize                   = 1;
    style.TabBorderSize                     = 1;
    style.WindowRounding                    = 7;
    style.ChildRounding                     = 4;
    style.FrameRounding                     = 2;
    style.PopupRounding                     = 0;
    style.ScrollbarRounding                 = 4;
    style.GrabRounding                      = 2;
    style.LogSliderDeadzone                 = 4;
    style.TabRounding                       = 4;

}

void setGuiScale(float guiScale) {
	int fbw, fbh, ww, wh;
	glfwGetFramebufferSize(Window::window, &fbw, &fbh);
	glfwGetWindowSize(Window::window, &ww, &wh);

	float pixelRatio = (float)fbw / ww;

	ImGui::GetIO().FontGlobalScale = guiScale / pixelRatio;
}









/////////////////////////////////////////// Implementation  //////////////////////////////////////////

void init(){
    using namespace std;

    // Attempt to initialize GLFW
	if (!glfwInit())
	{
		//Initialization failed
		cout << "GLFW initialization failed :(";
		//Use the close() function to safely close the application
		close();
	}


	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only


	//Set GLFW's error callback function
	glfwSetErrorCallback(error_callback);

	//GLFW creates a window and its OpenGL context with the next function
	Window::window = glfwCreateWindow(1024, 600, "panogui", glfwGetPrimaryMonitor(), NULL);

	//Check for errors (which would happen if creating a window fails
	if (!Window::window)
	{
		// Window or OpenGL context creation failed
		cerr << "GLFW failed to create a window and/or OpenGL context :(";
		//Use the terminate() function to safely close the application
		close();
	}

	//Window creation was successful. Continue
	glfwMakeContextCurrent(Window::window);
	glfwSwapInterval(1); // Enable vsync

	if (!gladLoadGL()) {
		// GLAD failed
		cerr << "GLAD failed to initialize :(";
		//Use the terminate() function to safely close the application
		close();
	}


    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    setStyle();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Window::window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Background
    glfwGetFramebufferSize(Window::window, &Window::width, &Window::height);
    printf("%d %d\n", Window::width, Window::height);

    cout << app::list.size() << " apps loaded" << endl;
}// end init()


void update(){
    //////////////////////////////////      1. Checks      //////////////////////////////////////
    // Make sure we have a window to draw on
    if(!Window::window){
        throw std::runtime_error("Window expected to be updated, but no window was created.");
    }
    // Let the user close the window
    if(glfwWindowShouldClose(Window::window)){
        close();
    }

    
    //////////////////////////////////      2. Pre-drawing      //////////////////////////////////////
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
    //glfwWaitEvents(); // More efficient
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::SetMouseCursor(ImGuiMouseCursor_None);
    ImGui::PushFont(Window::font);
    
    ImGuiID dockspace_id = ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    

    //////////////////////////////////      3. Draw applications      //////////////////////////////////////
    for(auto a: app::list){
        ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Always);
        a->uiDraw();
    }

    // ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Always);
    // ImGui::ShowDemoWindow(NULL);

    // ImGui::SetNextWindowDockID(dockspace_id, ImGuiCond_Always);
    // ImGui::Begin("Overlay", NULL);
    // if(ImGui::Button("Shader 0: Topologica")) std::cout << "button clicked" << std::endl;
    // ImGui::End();

    //////////////////////////////////      4. Rendering      //////////////////////////////////////
    ImGui::PopFont();
    ImGui::EndFrame();
    ImGui::Render();
    glClearColor(
        Window::background_color.x, 
        Window::background_color.y, 
        Window::background_color.z, 
        Window::background_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }

    glfwSwapBuffers(Window::window);
} // End update()


void close(){
    // Don't do anything if we aren't initialized
    if(!Window::window) return;
    // Apps
    for(auto a: app::list){
        a->uiClose();
    }
    // Imgui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // GLFW
    glfwDestroyWindow(Window::window);
    glfwTerminate();
    Window::window = NULL;
}


}