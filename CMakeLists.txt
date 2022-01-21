##################################################    Project     ##################################################
cmake_minimum_required(VERSION 3.20)

# Set project name & version
Project(VulkanPlayground VERSION 1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Specify the C++ standard
Set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(set_max_warning_level)
set_max_warning_level ()

# Set bin dir
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${BIN_DIR})

##################################################    Options     ##################################################
# option(VARIABLE "Descriptor" OFF)

##################################################    Sources     ##################################################

file(GLOB SOURCE_LIST
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
)

##################################################  Dependencies  ##################################################
# External Dependencies
# Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
list(APPEND PROJECT_LIBRARIES Vulkan::Vulkan)

if (EXISTS ${PROJECT_SOURCE_DIR}/extern/glm/CMakeLists.txt)
  add_subdirectory(extern/glm)
  list(APPEND PROJECT_LIBRARIES glm::glm)
else()
  find_package(glm REQUIRED)
  list(APPEND PROJECT_LIBRARIES glm::glm)
endif()

if (EXISTS ${PROJECT_SOURCE_DIR}/extern/glfw/CMakeLists.txt)
  option(GLFW_BUILD_EXAMPLES "" OFF)
  option(GLFW_BUILD_TESTS "" OFF)
  option(GLFW_BUILD_DOCS "" OFF)
  option(GLFW_INSTALL "" OFF)
  add_subdirectory(extern/glfw)
  list(APPEND PROJECT_LIBRARIES glfw)
else()
  find_package(glfw REQUIRED)
  list(APPEND PROJECT_LIBRARIES glfw)
endif()

if (EXISTS ${PROJECT_SOURCE_DIR}/extern/tinyobjloader/CMakeLists.txt)
  add_subdirectory(extern/tinyobjloader)
  list(APPEND PROJECT_LIBRARIES tinyobjloader)
else()
  find_package(tinyobjloader REQUIRED)
  list(APPEND PROJECT_LIBRARIES tinyobjloader)
endif()

add_library(stb_image INTERFACE)
target_sources(stb_image INTERFACE extern/stb_image/stb_image.h)
target_include_directories(stb_image INTERFACE extern/stb_image)
list(APPEND PROJECT_LIBRARIES stb_image)

# ADD LIBRARIES HERE.
# Examples:
# - Header Only:
#   find_package  (GLM REQUIRED)
#   import_library(GLM_INCLUDE_DIRS)
# - Identical Debug and Release:
#   find_package  (OpenGL REQUIRED)
#   import_library(OPENGL_INCLUDE_DIR OPENGL_LIBRARIES)
# - Separate Debug and Release:
#   find_package  (Boost REQUIRED iostreams)
#   import_library(Boost_INCLUDE_DIRS Boost_IOSTREAMS_LIBRARY_DEBUG Boost_IOSTREAMS_LIBRARY_RELEASE)
# - You may also set the PROJECT_INCLUDE_DIRS and PROJECT_LIBRARIES instead of using import_library.
##################################################    Targets     ##################################################

add_executable(VulkanPlayground ${SOURCE_LIST})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIBRARIES})

target_include_directories(VulkanPlayground PUBLIC
  # Main Project files
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
)

