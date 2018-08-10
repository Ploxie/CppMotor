#pragma once
#include "stdafx.h"

namespace Vulkan
{
	enum class VulkanMemoryUsage
	{
		/**
		Device local without host visible, use for resourecs that reside on GPU
		or only get changed once or infrequently
		Usage:
		- Resources written and read by device, e.g. images used as attachments.
		- Resources transferred from host once (immutable) or infrequently and read by
		device multiple times, e.g. textures to be sampled, vertex buffers, uniform
		(constant) buffers, and majority of other types of resources used by device.
		*/
		GPU_ONLY = 0,

		/**
		Memory mappable on host, (System memory, not GPU memory)
		HOST_VISIBLE and HOST_COHERENT
		CPU read may be slow
		Usage: Staging copy of resources used as transfer source.
		*/
		CPU_ONLY = 1,

		/**
		Memory that is both mappable on host (guarantees to be `HOST_VISIBLE`) and preferably fast to access by GPU.
		CPU reads may be uncached and very slow.
		Usage: Resources written frequently by host (dynamic), read by device. E.g. textures, vertex buffers, uniform buffers updated every frame or every draw call.
		*/
		CPU_TO_GPU = 2,

		/** Memory mappable on host (guarantees to be `HOST_VISIBLE`) and cached.
		It is roughly equivalent of `D3D12_HEAP_TYPE_READBACK`.
		Usage:
		- Resources written by device, read by host - results of some computations, e.g. screen capture, average scene luminance for HDR tone mapping.
		- Any resources read or accessed randomly on host, e.g. CPU-side copy of vertex buffer used as source of transfer, but also used for collision detection.
		*/
		GPU_TO_CPU = 3
	};
}