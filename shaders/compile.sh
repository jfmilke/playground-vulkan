# GLSL to SPIR-V Compiler (Linux) UNTESTED
# This little batch will compile glsl shaders into SPIR-V as needed by Vulkan.
# If VULKAN_SDK is not set, you need to use a hardcoded path as done in the first part.
# In this case you will most likely need to exchange the version of the path.

if [[ -z "${VULKAN_SDK}" ]]; then
  echo "Variable VULKAN__SDK is NOT defined, choosing hardcoded path"
  /home/$USER/VulkanSDK/1.2.198.1/x86_64/bin/glslc shader.vert -o vert.spv
  /home/$USER/VulkanSDK/1.2.198.1/x86_64/bin/glslc shader.frag -o frag.spv
else
  ${VULKAN_SDK}/x86_64/bin/glslc shader.vert -o vert.spv
  ${VULKAN_SDK}/x86_64/bin/glslc shader.frag -o frag.spv
fi
