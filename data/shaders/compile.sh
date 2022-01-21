# GLSL to SPIR-V Compiler (Linux) UNTESTED
# This little batch will compile glsl shaders into SPIR-V as needed by Vulkan.
# If VULKAN_SDK is not set, you need to use a hardcoded path as done in the first part.
# In this case you will most likely need to exchange the version of the path.

COMMAND_AVAILABLE=$(command -v glslc)

if [ ${COMMAND_AVAILABLE} ]
then
  glslc shader.vert -o vert.spv
  glslc shader.frag -o frag.spv
  echo "Done"
else
  echo "Could not execute glslc"
fi
