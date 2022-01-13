##################################################    Project     ##################################################
CMAKE_minimum_required(VERSION 3.20)

# Set project name & version
Project(VulkanPlayground VERSION 1.0 LANGUAGES CXX)

List(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# Specify the C++ standard
Set(CMAKE_CXX_STANDARD 17)
Set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

Set_Property(GLOBAL PROPERTY USE_FOLDERS ON)

Include(set_max_warning_level)
set_max_warning_level ()

##################################################    Options     ##################################################
# option(VARIABLE "Descriptor" OFF)

##################################################    Sources     ##################################################
Include_Directories(
  # Main Project files
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source
)

File(GLOB SOURCE_LIST
  "${PROJECT_SOURCE_DIR}/include/*.hpp"
  "${PROJECT_SOURCE_DIR}/source/*.cpp"
)

##################################################  Dependencies  ##################################################
# External Dependencies
# Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
List(APPEND PROJECT_INCLUDES ${Vulkan_INCLUDE_DIR})
List(APPEND PROJECT_LIBRARIES ${Vulkan_LIBRARIES})

# Submodule Dependencies:
## GLM
Add_Subdirectory(libraries/glm)
List(APPEND PROJECT_LIBRARIES glm)

## GLFW
Add_Subdirectory(libraries/glfw)
List(APPEND PROJECT_INCLUDES libraries/glfw/include)
List(APPEND PROJECT_LIBRARIES glfw ${GLFW_LIBRARIES})

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

Include_Directories(${PROJECT_INCLUDES})
##################################################    Targets     ##################################################

Add_Executable(VulkanPlayground ${SOURCE_LIST})

Target_Link_Libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LIBRARIES})

Target_Include_Directories(VulkanPlayground PUBLIC
                            "${PROJECT_BINARY_DIR}"
                          )
