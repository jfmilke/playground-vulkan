:: GLSL to SPIR-V Compiler (Windows)
:: This little batch will compile glsl shaders into SPIR-V as needed by Vulkan.
:: If VULKAN_SDK is not set, you need to use a hardcoded path as done in the first part.
:: In this case you will most likely need to exchange the version of the path.

@echo off

IF "%VULKAN_SDK%"=="" (
    ECHO Variable VULKAN__SDK is NOT defined, choosing hardcoded path
    C:\VulkanSDK\1.2.198.1\Bin\glslc.exe shader.vert -o vert.spv
    C:\VulkanSDK\1.2.198.1\Bin\glslc.exe shader.frag -o frag.spv
) ELSE (
    %VULKAN_SDK%\Bin\glslc.exe shader.vert -o vert.spv
    %VULKAN_SDK%\Bin\glslc.exe shader.frag -o frag.spv
)

pause
