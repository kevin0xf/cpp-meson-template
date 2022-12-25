#include "Window.h"

#include <stb/stb_image.h>

namespace Vortex {
    Window::Window(WindowCreateInfo info, std::function<void(float, Window&)> update_callback) : update_callback(update_callback) {
        NativeWindowInfo native_info;
        if(info.icon_path.length()) {
            int width, height;
            ImageInfo image_info;
            image_info.pixels = stbi_load("assets/Vortex.png", &width, &height, nullptr, 4);
            native_info.icon = image_info;
        }

        window = NativeWindow::create(native_info);

        if(info.icon_path.length()) {
            stbi_image_free(native_info.icon.pixels);
        }
    }
}
