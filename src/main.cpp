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
#include <algorithm>

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

    int createInstance() {
        vk::ApplicationInfo appInfo = {}; 
        appInfo.pApplicationName    = "Hello Triangle",
        appInfo.applicationVersion  = VK_MAKE_VERSION( 1, 0, 0 ),
        appInfo.pEngineName         = "No Engine",
        appInfo.engineVersion       = VK_MAKE_VERSION( 1, 0, 0 ),
        appInfo.apiVersion          = vk::ApiVersion14;

        // Get the required instance extensions from GLFW.
        uint32_t glfwExtensionCount = 0;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        // Check if the required GLFW extensions are supported by the Vulkan implementation.
        auto extensionProperties = context.enumerateInstanceExtensionProperties();
        for (uint32_t i = 0; i < glfwExtensionCount; ++i)
        {            
            if (std::ranges::none_of(extensionProperties,
                                    [glfwExtension = glfwExtensions[i]](auto const& extensionProperty)
                                    { return strcmp(extensionProperty.extensionName, glfwExtension) == 0; }))
            {
                throw std::runtime_error("Required GLFW extension not supported: " + std::string(glfwExtensions[i]));
            }
        }


        vk::InstanceCreateInfo createInfo  = {};
        createInfo.pApplicationInfo        = &appInfo;
        createInfo.enabledExtensionCount   = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        try {
            auto extensions = context.enumerateInstanceExtensionProperties();
            std::cout << "Available extensions:\n";

            for (const auto& extension : extensions) {
                std::cout << '\t' << extension.extensionName << '\n';
            }

            instance = vk::raii::Instance(context, createInfo);
            vk::raii::PhysicalDevice physicalDevice = instance.enumeratePhysicalDevices().front();
            vk::raii::Device device(physicalDevice, vk::DeviceCreateInfo{});

            vk::raii::Buffer buffer(device, vk::BufferCreateInfo{});
        }
        catch (const vk::SystemError& err) {
            std::cerr << "Vulkan error: " << err.what() << std::endl;
            return 1;
        }
        catch (const std::exception& err) {
            std::cerr << "Error: " << err.what() << std::endl;
            return 1;
        }
        return 0;
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
