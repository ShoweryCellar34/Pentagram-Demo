#include <Pentagram.hpp>

float rgb[] = {1, 0, 0};
int step = 5;
bool showDemoWindow = true;
glm::vec2 movment = {0, 0};
std::string logoPath = "";
PNT::image logo(logoPath.c_str());

void eventCallback(PNT::Window *window, PNT::windowEvent event) {
    if(event.eventType == PNT_EVENT_TYPE_KEYBOARD) {
        switch(event.keyboardEvent.key) {
        case GLFW_KEY_1:
            rgb[0] = 1;
            rgb[1] = 0;
            rgb[2] = 0;
            break;

        case GLFW_KEY_2:
            rgb[0] = 0;
            rgb[1] = 0;
            rgb[2] = 1;
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
            if(event.keyboardEvent.action == GLFW_PRESS) movment[0] += 1;
            if(event.keyboardEvent.action == GLFW_RELEASE) movment[0] += -1;
            break;

        case GLFW_KEY_LEFT:
            if(event.keyboardEvent.action == GLFW_PRESS) movment[0] += -1;
            if(event.keyboardEvent.action == GLFW_RELEASE) movment[0] += 1;
            break;

        case GLFW_KEY_UP:
            if(event.keyboardEvent.action == GLFW_PRESS) movment[1] += -1;
            if(event.keyboardEvent.action == GLFW_RELEASE) movment[1] += 1;
            break;

        case GLFW_KEY_DOWN:
            if(event.keyboardEvent.action == GLFW_PRESS) movment[1] += 1;
            if(event.keyboardEvent.action == GLFW_RELEASE) movment[1] += -1;
            break;
        }
        window->setPosition(window->getWindowData().xpos + (movment[0] * step), window->getWindowData().ypos + (movment[1] * step));
    }
}

void startFrameCallback(PNT::Window *window) {
    // Set background color.
    window->setClearColor(rgb[0], rgb[1], rgb[2], 1);

    // ImGui GUI.
    ImGui::Begin("Demo Controls");

    // Logo Path.
    ImGui::Text("Logo Path: ");
    ImGui::SameLine();
    ImGui::InputText("##InputText 0", &logoPath);

    // Clear Color.
    ImGui::Text("Background Color: ");
    ImGui::ColorPicker3("##ColorPicker3 0", rgb, ImGuiColorEditFlags_InputRGB);
    ImGui::Text("Reposition Step: ");
    ImGui::SameLine();
    ImGui::SliderInt("##SliderInt 0", &step, 1, 20, "%d", ImGuiSliderFlags_AlwaysClamp);

    // Demo Window.
    if(ImGui::Button(showDemoWindow ? "Hide Demo Window ##Button 0" : "Show Demo Window ##Button 0")) showDemoWindow = !showDemoWindow;
    if(showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

    ImGui::End();

    logo.setData(logoPath.c_str());
    if(logo.valid()) window->setIcon(logo);
}

int main(int argc, char *argv[]) {
    // Initilize.
    PNT::init();

    // Creating window
    PNT::Window window("Demo Window", 600, 600, 700, 400, ImGuiConfigFlags_ViewportsEnable | ImGuiConfigFlags_DockingEnable);

    // Setting callbackss
    window.setCallback(PNT_CALLBACK_FLAGS_STARTFRAME, &startFrameCallback);
    window.setEventCallback(&eventCallback);

    // App loop
    while(!window.shouldClose()) {
        // Event processing.
        PNT::processEvents();

        // Start and end frame.
        window.startFrame();
        window.endFrame();
    }

    // Shutdown.
    PNT::deinit();
    return 0;
}
