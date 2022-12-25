#pragma once
#include <functional>

#include <Core.h>
#include <math/Types.h>

using namespace Math;

namespace Vortex {
    struct ImageInfo {
        Vector2UI dimension;
        u8* pixels;
    };

    struct NativeWindowInfo {
        String title;
        Vector2UI dimension;
        ImageInfo icon;
    };

    class NativeWindow {
    public:
        virtual ~NativeWindow() = default;

        virtual Vector2UI getDimension() = 0;
        virtual Vector2UI getPosition() = 0;

        virtual void update() = 0;

        static NativeWindow* create(NativeWindowInfo info);
    };

    struct WindowCreateInfo {
        String title;
        Vector2UI dimension;
        String icon_path;
    };
    
    class Window {
        NativeWindow* window;
        std::function<void(float, Window&)> update_callback;
    public:
        Window(WindowCreateInfo info, std::function<void(float, Window&)> update_callback);

        ~Window() {
            delete window;
        }

    };
}
