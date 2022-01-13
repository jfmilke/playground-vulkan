#pragma once

#include <vulkan/vulkan.hpp>

// Forward declarations
struct GLFWwindow;

// Constants
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

// Code
class HelloTriangleApp {
public:
  void run();

private:
  void initWindow();
  void initVulkan();
  void createInstance();
  void setupDebugMessenger();
  void mainLoop();
  void cleanUp();

private:
  bool checkValidationLayerSupport();
  std::vector<const char*> getRequiredExtensions();

private:
  GLFWwindow* window;

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
};

int main();