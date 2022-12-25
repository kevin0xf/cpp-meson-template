#include "vortex/window/Window.h"
#include <GLFW/glfw3.h>

namespace Vortex {
    class GLFWWindow : public NativeWindow {
    private:
        GLFWwindow* window;
    public:
        GLFWWindow(NativeWindowInfo windowInfo) {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            window = glfwCreateWindow(windowInfo.dimension.x(), windowInfo.dimension.y(), windowInfo.title.c_str(), NULL, NULL);

            GLFWimage image = {
                (int)windowInfo.icon.dimension.x(),
                (int)windowInfo.icon.dimension.y(),
                windowInfo.icon.pixels
            };

            glfwSetWindowIcon(window, 1, &image);

        }

        ~GLFWWindow() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        Vector2UI getDimension() override {
            return {};
        }

        Vector2UI getPosition() override {
            return {};
        }

        void update() override {

        }
    };
    
    NativeWindow* NativeWindow::create(NativeWindowInfo windowInfo) {
        return new GLFWWindow(windowInfo);
    }
    

}