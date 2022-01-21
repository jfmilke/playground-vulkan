# VulkanPlayground
As the name indicates a small playground to learn Vulkan.
Following vulkan-tutorial.com.

## Requirements
- CMake 3.20+
- GCC 9+ or Visual Studio 2019+
- [Vulkan SDK by LunarG 1.2.198.1+](https://sdk.lunarg.com/sdk/download/1.2.198.1/windows/VulkanSDK-1.2.198.1-Installer.exe)
    - Untested for Linux, check [this](https://vulkan-tutorial.com/Development_environment)

## Dependencies
- glm *(submodule available)*
- glfw3 *(submodule available)*
- stb_image *(included)*

The `extern` folder contains git submodules pointing to the required dependencies, except for the `stb_image` library which is directly contained in this repository.
Git submodules need to be cloned **explicitly.**
This means, you can decide for yourself if you want to use already existing libraries somewhere on your system or if you want to download and build everything in place.

## Building
This project is meant to be cross compatible between Linux and Windows (at least) and easy to setup.

### Windows

If you use Git Bash cloning is similar to Linux:
```bash
# with submodules
git clone --recurse-submodules <git-url>
# or without submodules
# git clone <git-url>
```

If you use GitHub Desktop it will possibly automatically download the submodules without question.
In this case delete all subfolders of `extern` **except for `stb_image`.**

Don't forget to compile the shaders via `data/shaders/compile.bat`.

### Linux

```bash
# with submodules
git clone --recurse-submodules <git-url>
# or without submodules
# git clone <git-url>
cd playground-vulkan
mkdir build
cd build
cmake ..
make
../bin/VulkanPlayground
```

Don't forget to compile the shaders via `data/shaders/compile.sh`.
You may need to make it executable via `sudo chmod +x data/shaders/compile.sh`.
