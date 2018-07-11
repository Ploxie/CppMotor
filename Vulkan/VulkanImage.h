#pragma once
#include "stdafx.h"

namespace Vulkan
{
	typedef VkImageType ImageType;
	typedef VkImageUsageFlags ImageUsageFlags;
	typedef VkImageLayout ImageLayout;

	class Image
	{
	public:
		inline Image(const VkImage& image, const ImageType& type, const ImageLayout& layout, const uint& width, const uint& height, const uint& depth);

		inline const VkImage& GetHandle() const;
		inline const ImageType& GetType() const;
		inline const ImageLayout& GetLayout() const;
		inline const uint& GetWidth() const;
		inline const uint& GetHeight() const;
		inline const uint& GetDepth() const;

	private:
		const VkImage internal;
		const ImageType type;
		const ImageLayout layout;

		const uint width;
		const uint height;
		const uint depth;
	};

	inline Image::Image(const VkImage& image, const ImageType& type, const ImageLayout& layout, const uint& width, const uint& height, const uint& depth)
		: internal(image), type(type), layout(layout), width(width), height(height), depth(depth)
	{

	}

	inline const VkImage& Image::GetHandle() const
	{
		return internal;
	}

	inline const ImageType& Image::GetType() const
	{
		return type;
	}

	inline const ImageLayout& Image::GetLayout() const
	{
		return layout;
	}

	inline const uint& Image::GetWidth() const
	{
		return width;
	}

	inline const uint& Image::GetHeight() const
	{
		return height;
	}

	inline const uint& Image::GetDepth() const
	{
		return depth;
	}
}