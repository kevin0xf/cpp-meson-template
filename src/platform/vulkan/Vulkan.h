#pragma once

#include <vector>

#include <src/Core.h>
#include <vulkan/vulkan.h>

namespace Vortex {
    namespace Vulkan {
        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

        std::vector<const char*> getRequiredExtensions();
        void printExtensions();
    }
}
