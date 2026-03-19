#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void createInstance() {
        vk::ApplicationInfo appInfo = {}; 
        appInfo.pApplicationName    = "Hello Triangle",
        appInfo.applicationVersion  = VK_MAKE_VERSION( 1, 0, 0 ),
        appInfo.pEngineName         = "No Engine",
        appInfo.engineVersion       = VK_MAKE_VERSION( 1, 0, 0 ),
        appInfo.apiVersion          = vk::ApiVersion14;

        vk::InstanceCreateInfo createInfo = {};
        createInfo.pApplicationInfo       = &appInfo;

        instance = vk::raii::Instance(context, createInfo);
    }

    void initVulkan() {
        createInstance();
    }

    void mainLoop() {

    }

    void cleanup() {

    }

    vk::raii::Context context;
    vk::raii::Instance instance = nullptr;
};

int main()
{
    try
    {
        HelloTriangleApplication app;
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    // std::cout << __cplusplus << std::endl;
    return EXIT_SUCCESS;
}