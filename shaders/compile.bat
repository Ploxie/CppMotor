@echo off
for %%i in (*.vert) do C:/VulkanSDK/1.1.70.1/Bin32/glslangValidator.exe -V %%i -o %%i.spv
for %%i in (*.frag) do C:/VulkanSDK/1.1.70.1/Bin32/glslangValidator.exe -V %%i -o %%i.spv
