#include <PentagramExt.hpp>
#include <random>

bool shouldClose = false;
float rgb[] = {1, 0, 0};
unsigned char step = 5;

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
            window->setPosition(500, 500);
            break;

        case GLFW_KEY_EQUAL:
            if(step < 20) step++;
            break;

        case GLFW_KEY_MINUS:
            if(step > 1) step--;
            break;

        case GLFW_KEY_UP:
            window->setPosition(-1, window->getWindowData().y - step);
            break;

        case GLFW_KEY_DOWN:
            window->setPosition(-1, window->getWindowData().y + step);
            break;

        case GLFW_KEY_LEFT:
            window->setPosition(window->getWindowData().x - step, -1);
            break;

        case GLFW_KEY_RIGHT:
            window->setPosition(window->getWindowData().x + step, -1);
            break;
        }
    }
    //if(PNT::getEvent().window.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {shouldClose = true;}
}

void startFrameCallback(PNT::Window *window) {
    // Set background color.
    window->setClearColor(rgb[0], rgb[1], rgb[2]);

    // ImGui gui.
    ImGui::Begin("Demo Controls");

    ImGui::Text("Background Color: ");
    ImGui::ColorPicker3("##ColorPicker3 0", rgb, ImGuiColorEditFlags_InputRGB);

    ImGui::Text("Reposition Step: ");
    ImGui::SameLine();
    ImGui::SliderInt("##SliderInt 0", (int *)&step, 1, 20, "%d", ImGuiSliderFlags_AlwaysClamp);

    ImGui::End();

    ImGui::ShowDemoWindow();
}

int main(int argc, char *argv[]) {
    // Init
    PNT::init();

    // Creating window
    PNT::Window window("Demo Window", 600, 600);

    // Setting callbackss
    window.setCallback(PNT_CALLBACK_FLAGS_STARTFRAME, &startFrameCallback);
    window.setEventCallback(&eventCallback);

    // App loop
    while(!shouldClose) {
        // Event processing
        glfwPollEvents();

        // Start and end frame
        window.startFrame();
        window.endFrame();
    }

    // Deinit
    PNT::deinit();
    return 0;
}
