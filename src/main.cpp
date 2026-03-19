#if defined(__INTELLISENSE__) || !defined(USE_CPP20_MODULES)
#include <vulkan/vulkan_raii.hpp>
#else
import vulkan_hpp;
#endif
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
    void initVulkan() {

    }

    void mainLoop() {

    }

    void cleanup() {

    }
};

int main()
{
    // constexpr vk::ApplicationInfo appInfo{.pApplicationName   = "Hello Triangle",
    //                                   .applicationVersion = VK_MAKE_VERSION( 1, 0, 0 ),
    //                                   .pEngineName        = "No Engine",
    //                                   .engineVersion      = VK_MAKE_VERSION( 1, 0, 0 ),
    //                                   .apiVersion         = vk::ApiVersion14};

    // vk::InstanceCreateInfo createInfo{
    //     .pApplicationInfo = &appInfo
    // };

    // instance = vk::raii::Instance(context, createInfo);
    
    // try
    // {
    //     HelloTriangleApplication app;
    //     app.run();
    // }
    // catch (const std::exception& e)
    // {
    //     std::cerr << e.what() << std::endl;
    //     return EXIT_FAILURE;
    // }

    std::cout << __cplusplus << std::endl;
    return EXIT_SUCCESS;
}