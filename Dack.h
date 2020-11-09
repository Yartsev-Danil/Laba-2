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
	void Clear(){
		if (this->items->GetSize() <= 0)
			throw std::logic_error("size error");
		for (int i = this->items->GetSize() - 1; i > 0; i--)
			this->items->RemoveAt(i);
		delete[] this->items;
	}
};