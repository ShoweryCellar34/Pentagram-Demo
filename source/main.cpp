#include <PNT/Pentagram.hpp>

float rgba[] = {1, 0, 0, 1};
int step = 5;
bool showDemoWindow = true;
int movment[2] = {0, 0};

// Event callback
void eventCallback(PNT::Window *window, PNT::windowEvent event) {
    if(event.type == PNT_EVENT_TYPE_KEYBOARD) {
        switch(event.keyboard.key) {
        case GLFW_KEY_1:
            rgba[0] = 1;
            rgba[1] = 0;
            rgba[2] = 0;
            break;

        case GLFW_KEY_2:
            rgba[0] = 0;
            rgba[1] = 0;
            rgba[2] = 1;
            break;

        case GLFW_KEY_BACKSPACE:
            window->setPosition(700, 500);
            break;

        case GLFW_KEY_EQUAL:
            if(step < 20) step++;
            break;

        case GLFW_KEY_MINUS:
            if(step > 1) step--;
            break;

        case GLFW_KEY_RIGHT:
            if(event.keyboard.action == GLFW_PRESS) movment[0] += 1;
            if(event.keyboard.action == GLFW_RELEASE) movment[0] += -1;
            break;

        case GLFW_KEY_LEFT:
            if(event.keyboard.action == GLFW_PRESS) movment[0] += -1;
            if(event.keyboard.action == GLFW_RELEASE) movment[0] += 1;
            break;

        case GLFW_KEY_UP:
            if(event.keyboard.action == GLFW_PRESS) movment[1] += -1;
            if(event.keyboard.action == GLFW_RELEASE) movment[1] += 1;
            break;

        case GLFW_KEY_DOWN:
            if(event.keyboard.action == GLFW_PRESS) movment[1] += 1;
            if(event.keyboard.action == GLFW_RELEASE) movment[1] += -1;
            break;
        }
        window->setPosition(window->getWindowData().xpos + (movment[0] * step), window->getWindowData().ypos + (movment[1] * step));
    }
}

int main(int argc, char *argv[]) {
    PNT::init();

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    PNT::Window window("Demo Window", 600, 600, 700, 400, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable);

    window.setEventCallback(&eventCallback);

    while(!window.shouldClose()) {
        PNT::processEvents();

        window.startFrame();

        // Set background color.
        window.setClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);

        // ImGui GUI.
        ImGui::Begin("Demo Controls");

        // Clear Color.
        ImGui::Text("Background Color: ");
        ImGui::ColorPicker3("##ColorPicker3 0", rgba, ImGuiColorEditFlags_InputRGB);
        ImGui::Text("Alpha channel: ");
        ImGui::SameLine();
        ImGui::SliderFloat("##SliderFloat 0", &rgba[3], 0.0f, 1.0f, "%f", ImGuiSliderFlags_AlwaysClamp);
        ImGui::Text("Reposition Step: ");
        ImGui::SameLine();
        ImGui::SliderInt("##SliderInt 0", &step, 1, 20, "%d", ImGuiSliderFlags_AlwaysClamp);

        // Demo Window.
        if(ImGui::Button(showDemoWindow ? "Hide Demo Window ##Button 0" : "Show Demo Window ##Button 0")) showDemoWindow = !showDemoWindow;
        if(showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

        ImGui::End();

        window.endFrame();
    }

    PNT::deinit();
    return 0;
}
