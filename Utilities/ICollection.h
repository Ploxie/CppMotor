#pragma once
#include "BasicTypes.h"

namespace Collections
{
	template<typename T>
	class ICollection
	{
	public:
		virtual const T& Add() = 0;
		virtual const T& Add(const T& object) = 0;

		virtual void Clear() = 0;

		virtual bool Contains(const T& object) const = 0;

		virtual void Remove(const T& object) = 0;

		virtual const uint Count() const = 0;
		
	};
}