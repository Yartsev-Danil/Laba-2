#pragma once

#include "Optional.h"
#include<stdexcept>

template <class T>
class DynamicArray
{
private:
	Optional<T>* items;
	int size;
public:
	DynamicArray(T* items, const int size) {
		if (!items)
			throw std::logic_error("no items");
		if (size < 1)
			throw std::logic_error("size error");
		this->items = static_cast<Optional<int>*>(operator new[](size * sizeof(Optional<int>)));
		for (int i = 0; i < size; i++)
		{
			this->items[i].Set(items[i]);
			
		}
		this->size = size;
	}
	DynamicArray(const int size)
	{
		if (size < 1)
			throw std::logic_error("size error");
		this->items = static_cast<Optional<int>*>(operator new[](size * sizeof(Optional<int>)));
		for (int i = 0; i < size; i++)
			this->items[i] = *Optional<T>::Empty();
		this->size = size;

	}
	DynamicArray(const DynamicArray<T>& array) {
		if (array.size < 0 || !array.items)
			throw std::out_of_range("index out of range");
		this->items = static_cast<Optional<int>*>(operator new[](size * sizeof(Optional<int>)));

		for (int i = 0; i < array.size; i++)
		{
			this->items[i] = array.items[i];
		};
		this->size = array.size;
	}
public:
	int GetSize() const { return this->size; }
	T Get(const int index) const
	{
		if (index < 0 || index >= this->size || !this->items->HasValue())
			throw std::out_of_range("index out of range");
		return this->items[index].GetValue();
	}
public:
	bool HasValue(const int index) {
		if (index < 0 || index >= this->size || !this->size || !this->items)
			throw std::out_of_range("index out of range");
		return this->items[index].HasValue();
	}
	void Set(const int index, const T value)
	{
		if (index < 0 || index >= this->size)
			throw std::out_of_range("index out of range");
		this->items[index].Set(value);
	}
	void Resize(int newSize) {
		if (newSize <= 0)
			throw std::logic_error("size error");
		if (newSize == this->size)
			return;
		Optional<T>* new_items = static_cast<Optional<int>*>(operator new[](size * sizeof(Optional<int>)));
		if (newSize > this->size)
		{
			int i;
			for (i = 0; i < this->size; i++)
			{
				if (this->items[i].HasValue())
				{
					new_items[i].Set(this->items[i]);
					new_items[i].SetHasValue(true);
				}
				else
					new_items[i].SetHasValue(false);
			};
			for (i; i < newSize; i++)
				new_items[i].SetHasValue(false);
		}
		else
		{
			for (int i = 0; i < newSize; i++)
			{
				if (this->items[i].HasValue())
				{
					new_items[i].Set(this->items[i]);
					new_items[i].SetHasValue(true);
				}
				else
					new_items[i].SetHasValue(false);
			};
		};
		this->size = newSize;
		delete[] this->items;
		this->items = new_items;
	}

};
