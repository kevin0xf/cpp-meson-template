#pragma once

#include "Vulkan.h"

namespace Vortex::Vulkan {
    class Instance {
    private:
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        bool checkValidationLayerSupport();
        static VkDebugUtilsMessengerCreateInfoEXT createDebugMessengerCreateInfo(PFN_vkDebugUtilsMessengerCallbackEXT callback);
    public:
        Instance();
        void create();
        void destroy();
        void setupDebugMessenger();
        
        operator VkInstance() {
            return instance;
        }
    };
}