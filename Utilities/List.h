#pragma once
#include "ICollection.h"

namespace Collections
{
	template<typename T, typename Alloc>
	class List final : public ICollection<T>
	{
	public:
		typedef Iterator T;
		static const uint NotFound = static_cast<uint>(-1);

		inline List();
		
		inline explicit List(const uint& capacity);
		inline explicit List(const T* anArray, const unsigned int count);
		
		inline ~List();

		inline List& operator=(const List& list);

		inline const T& Add() override;
		inline const T& Add(const T& object) override;

		inline T& At(const uint& index);
		inline const T& At(const uint& index) const;

		inline unsigned int Capacity() const;

		inline void Clear() override;

		inline uint Count() const override;

		inline uint IndexOf(const T& object) const;

		inline const T& Insert(const uint& index, const T& object);
		
		inline void Remove(const T& object) override;
		inline void RemoveAt(const uint& index);

		inline void RemoveCyclic(const T& object);
		inline void RemoveCyclicAt(const uint& index);

		inline void Sort();
		
		Iterator* Begin() { return &data[0]; }
		const Iterator* Begin() const { return &data[0]; }

		Iterator* End() { return &data[Count();  }
		const Iterator* End() const { return &data[Count()];  }

	private:
		inline T* AllocateMemory(const uint& capacity);
		inline void DeallocateMemory(T* memory);

		inline void GrowToFit(const uint& amount);

		inline void RemoveAllInternal();

		Alloc allocator;

		T* data;

		uint capacity;
		uint count;		
	};

	template<typename T, typename Alloc>
	inline List<T, Alloc>::List()
	{
		List(32);
	}

	template<typename T, typename Alloc>
	inline List<T, Alloc>::List(const uint& capacity)
	{
		this->capacity = capacity;
		this->count = 0;
		this->data = AllocateMemory(capacity);
	}

	template<typename T, typename Alloc>
	inline List<T, Alloc>::List(const T* anArray, const unsigned int count)
	{
		for (uint i = 0; i < count; ++i)
		{
			data[i] = anArray[i];
		}

		this->count = count;
	}

	template<typename T, typename Alloc>
	inline List<T, Alloc>::~List()
	{
		RemoveAllInternal();
		DeallocateMemory(data);
	}

	template<typename T, typename Alloc>
	List<T, Alloc>& List<T, Alloc>::operator=(const List<T, Alloc>& list)
	{
		RemoveAllInternal();
		DeallocateMemory(data);

		data = list.data;
		capacity = list.capacity;
		count = list.count;
		allocator = list.allocator;

		return *this;
	}

	template<typename T, typename Alloc>
	T& List<T, Alloc>::operator[](const uint& index)
	{
		return At(index);
	}

	template<typename T, typename Alloc>
	const T& List<T, Alloc>::operator[](const uint& index) const
	{
		return At(index);
	}

	template<typename T, typename Alloc>
	inline const T& List<T, Alloc>::Add()
	{
		GrowToFit(count + 1);
		T* object = new (&data[count]) T();
		count++;
		return *object;
	}

	template<typename T, typename Alloc>
	inline const T& List<T, Alloc>::Add(const T& object)
	{
		
	}

	template<typename T, typename Alloc>
	inline T& List<T, Alloc>::At(const uint& index)
	{

	}

	template<typename T, typename Alloc>
	inline const T& List<T, Alloc>::At(const uint& index) const
	{

	}

	template<typename T, typename Alloc>
	inline unsigned int List<T, Alloc>::Capacity() const
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::Clear()
	{

	}

	template<typename T, typename Alloc>
	inline uint List<T, Alloc>::Count() const
	{

	}

	template<typename T, typename Alloc>
	inline uint List<T, Alloc>::IndexOf(const T& object) const
	{

	}

	template<typename T, typename Alloc>
	inline const T& List<T, Alloc>::Insert(const uint& index, const T& object)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::Remove(const T& object)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::RemoveAt(const uint& index)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::RemoveCyclic(const T& object)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::RemoveCyclicAt(const uint& index)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::Sort()
	{

	}
	
	template<typename T, typename Alloc>
	inline T* List<T, Alloc>::AllocateMemory(const uint& capacity)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::DeallocateMemory(T* memory)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::GrowToFit(const uint& amount)
	{

	}

	template<typename T, typename Alloc>
	inline void List<T, Alloc>::RemoveAllInternal()
	{

	}

}