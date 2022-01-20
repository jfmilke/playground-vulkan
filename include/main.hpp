#pragma once

#include <vulkan/vulkan.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <optional>
#include <array>

// Forward declarations
struct GLFWwindow;

// Constants
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;
const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
  const bool enableValidationLayers = false;
#else
  const bool enableValidationLayers = true;
#endif

// Code
struct QueueFamilyIndices {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;
  std::optional<uint32_t> transferFamily;

  bool isComplete() {
    return graphicsFamily.has_value() && presentFamily.has_value();
  }

  bool hasTransferFamily() {
    return transferFamily.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
  glm::vec2 pos;
  glm::vec3 color;

  static VkVertexInputBindingDescription getBindingDescription() {
    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return bindingDescription;
  }

  static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};
    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, pos);
    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, color);

    return attributeDescriptions;
  }
};

struct UniformBufferObject {
  alignas(16) glm::mat4 model;
  alignas(16) glm::mat4 view;
  alignas(16) glm::mat4 proj;
};

class HelloTriangleApp {
public:
  void run();

private:
  void initWindow();
  void initVulkan();
  void createInstance();
  void createLogicalDevice();
  void createSurface();
  void createSwapChain();
  void createImageViews();
  void createRenderPass();
  void createGraphicsPipeline();
  void createDescriptorSetLayout();
  VkShaderModule createShaderModule(const std::vector<char>& code);
  void createFramebuffers();
  void createCommandPools();
  void createTextureImage();
  void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
  void createCommandBuffers();
  void createIndexBuffer();
  void createVertexBuffer();
  void createUniformBuffers();
  void createDescriptorPool();
  void createDescriptorSets();
  void createBuffer(VkDeviceSize deviceSize, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
  void createSyncObjects();
  void createVertexData();
  void recreateSwapChain();
  void setupDebugMessenger();
  void updateUniformBuffer(uint32_t currentImage);
  void mainLoop();
  void cleanupSwapChain();
  void cleanUp();

  void drawFrame();

  void pickPhysicalDevice();      // uses isDeviceSuitable
  void pickBestPhysicalDevice();  // uses rateDeviceSuitabiulity

  VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
  VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
  // sets resolution of swap chain images (in pixels)
  VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  VkCommandBuffer beginSingleTimeCommands();
  void endSingleTimeCommands(VkCommandBuffer commandBuffer);
  void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
  void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
  void copyBufferToImage(VkBuffer srcBuffer, VkImage dstImage, uint32_t width, uint32_t height);

private:
  bool checkValidationLayerSupport();
  std::vector<const char*> getRequiredExtensions();
  bool isDeviceSuitable(VkPhysicalDevice device);
  int rateDeviceSuitability(VkPhysicalDevice device); // alternative to isDeviceSuitable
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);
  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
  uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);


private:
  GLFWwindow* window;

private:
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkSurfaceKHR surface;

  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // is destroyed with VkInstance
  VkDevice device;

  VkQueue graphicsQueue; // is destroyed with VkDevice
  VkQueue presentQueue;
  VkQueue transferQueue;

  VkSwapchainKHR swapChain;
  std::vector<VkImage> swapChainImages; // are destroyed automatically with swapchain
  VkFormat swapChainImageFormat;
  VkExtent2D swapChainExtent;
  std::vector<VkImageView> swapChainImageViews;
  std::vector<VkFramebuffer> swapChainFramebuffers;

  VkRenderPass renderPass;
  VkDescriptorSetLayout descriptorSetLayout;
  VkPipelineLayout pipelineLayout;
  VkPipeline graphicsPipeline;

  VkCommandPool graphicsCommandPool;
  VkCommandPool transferCommandPool;

  std::vector<Vertex> vertexData;
  std::vector<uint16_t> indices;

  VkImage textureImage;
  VkDeviceMemory textureImageMemory;

  VkBuffer vertexBuffer;
  VkDeviceMemory vertexBufferMemory;
  VkBuffer indexBuffer;
  VkDeviceMemory indexBufferMemory;

  std::vector<VkBuffer> uniformBuffers;
  std::vector<VkDeviceMemory> uniformBuffersMemory;

  VkDescriptorPool descriptorPool;
  std::vector<VkDescriptorSet> descriptorSets;

  std::vector<VkCommandBuffer> commandBuffers;

  std::vector<VkSemaphore> imageAvailableSemaphores;
  std::vector<VkSemaphore> renderFinishedSemaphores;
  std::vector<VkFence> inFlightFences;
  std::vector<VkFence> imagesInFlight;
  size_t currentFrame = 0;

  bool framebufferResized = false;

private:
  const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
  };

private:
  static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};


int main();