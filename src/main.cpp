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

constexpr uint32_t WIDTH = 800;
constexpr uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        std::cout << "Initialized window, initializing Vulkan..." << std::endl;

        initVulkan();
        std::cout << "Initialized Vulkan, starting main loop..." << std::endl;

        mainLoop();
        std::cout << "Finished main loop, starting cleanup..." << std::endl;

        cleanup();
    }

private:
    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);

    }
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
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);

        glfwTerminate();
    }

    vk::raii::Context context;
    vk::raii::Instance instance = nullptr;
    GLFWwindow* window;
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