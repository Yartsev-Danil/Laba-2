#pragma once
#include "Sequence.h"
#include "ArraySequence.h"
#include<stdexcept>

template<class T>
class Deque {
private:
	Sequence<T>* items;
public:

	Deque() {
		this->items = new ArraySequence<T>();
	}

	Deque(const T* items, const int count)
	{
		this->items = new ArraySequence<T>();
		for (int i = 0; i < count; i++)
		{
			this->items->data->items[count].Set(items);
		}
	}

	Deque(Sequence<T>* items)
	{
		this->items = new ArraySequence<T>();
		for (int i = 0; i < items->GetLength(); i++)
			this->items->Append(items->Get(i));
	}
	void PushBack(const T value) {
		this->items->Append(value);
	}
	void PushFront(const T value) {
		this->items->Prepend(value);
	}
	void PopBack() {
		if (this->items->GetSize() <= 0)
			throw std::logic_error("size error");
		auto item = this->items->GetLast();
		this->items->RemoveAt(this->count - 1);

	}
	void PopFront() {
		if (this->items->GetSize() <= 0)
			throw std::logic_error("size error");
		auto item = this->items->GetFirst();
		this->items->RemoveAt(0);
	}
	bool IsEmpty() {
		if (this->items->GetSize() <= 0)
			throw std::logic_error("size error");
		if (this->items->data->HasValue())
			return true;
	}
	void Clear() {
		if (this->items->GetSize() <= 0)
			throw std::logic_error("size error");
		for (int i = this->items->GetSize() - 1; i > 0; i--)
			this->items->RemoveAt(i);
		delete[] this->items;
	}
	Deque<T>* Where(bool (*wfun)(T) const
	{
		if (!this->data || !this->data->GetLength())
			throw std::out_of_range("index out of range");
		Deque<T>* deque = new deque<T>();
		for (int i = 0; i < this->items->GetLength(); i++)
			if (wfun(this->items->Get(i)))
			{
				deque->items->Append(this->items->Get(i));
			};
		return deque;
	}
	Deque<T>* Map(T(*mfun)(T)) const
	{
		if (!this->data || !this->data->GetLength())
			throw std::out_of_range("index out of range");
		Deque<T>* deque = new Deque<T>(*(this));
		for (int i = 0; i < deque->items->GetLength(); i++)
		{
			deque->data->Set(i, mfun(this->data->Get(i)));
		};
		return deque;
	}
	T Reduce(T(*rfun)(T, T), T startvalue) const
	{
		if (!this->data || !this->data->GetLength())
			throw std::out_of_range("index out of range");
		for (int i = this->items->GetLength() - 1; i >= 0; i--)
		{
			startvalue = rfun(this->items->Get(i), startvalue);
		};
		return startvalue;
	}
};
