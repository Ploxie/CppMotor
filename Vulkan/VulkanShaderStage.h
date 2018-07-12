#pragma once
#include "stdafx.h"

namespace Vulkan
{

	typedef VkShaderStageFlagBits ShaderStageType;

	class ShaderStage
	{
	public:
		inline ShaderStage();
		inline ShaderStage(const VkShaderModule& module, const ShaderStageType& shaderType, const char* functionName = "main");

		inline const VkShaderModule& GetModule() const;
		inline const VkPipelineShaderStageCreateInfo& GetStageInfo() const;
	private:
		VkShaderModule module;
		VkPipelineShaderStageCreateInfo stageInfo;
	};

	inline ShaderStage::ShaderStage()
	{

	}

	inline ShaderStage::ShaderStage(const VkShaderModule& module, const ShaderStageType& shaderType, const char* functionName) : module(module)
	{
		stageInfo = {};
		stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		stageInfo.stage = shaderType;
		stageInfo.module = module;
		stageInfo.pName = functionName;

	}

	inline const VkShaderModule& ShaderStage::GetModule() const
	{
		return module;
	}

	inline const VkPipelineShaderStageCreateInfo& ShaderStage::GetStageInfo() const
	{
		return stageInfo;
	}
}