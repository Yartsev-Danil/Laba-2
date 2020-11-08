#pragma once
#include "Sequence.h"
#include "DynamicArray.h"
#include "ArraySequence.h"
template <class T>
class Stack
{
private:
	Sequence<T>* items;
public:
	Stack()
	{
		this->items = new ArraySequence<T>();
	}
	Stack(const T* items, const int count) 
	{
		this->items = new ArraySequence<T>();
		for(int i = 0; i < count; i++)
		{
			this->items->data->items[count].Set(items);
		}
	}
	Stack(Sequence<T>* items)
	{
		//this->items = items;
		this->items = new ArraySequence<T>();
		for (int i = 0; i < items->GetLength(); i++)
			this->items->Append(items->Get(i));
	}
	Stack(const Stack<T>& other) 
	{
		if (!other.data->GetLength())
			throw std::invalid_argument("invalid meanings of arguments");
		this->items = new ArraySequence<T>(other.items);
	}
public:
	T rfun(T value1, T value2);
	T mfun(T value);
	bool wfun(T value);
	int GetSize()
	{
		return this->items->GetLength();
	}
	bool IsEmpty()
	{
		return this->items->GetLength() == 0;
	}
	T Peek(const int index = 0) const
	{
		if (index < 0 || index >= this->items->GetLength())
			throw new Exception;
		return items->Get(index);
	}
	T Pop()
	{
		if (this->items->GetLength() <= 0)
			throw new Exception;
		auto item = this->items->GetFirst();
		this->items->RemoveAt(0);
		return item;
	}
public:
	void Push(T item)
	{
		this->items->Prepend(item);
	}
	
	Stack<T>* Map(T(*mfun)(T)) const 
	{
		if (!this->data || !this->data->GetLength())
			throw std::out_of_range("index out of range");
		Stack<T>* stack = new Stack<T>(*(this));
		for (int i = 0; i < stack->items->GetLength(); i++)
		{
			stack->data->Set(i, mfun(this->data->Get(i)));
		};
		return stack;
	}
	Stack<T>* Where(bool (*wfun)(T) const
	{
		if (!this->data || !this->data->GetLength())
			throw std::out_of_range("index out of range");
		Stack<T>* stack = new Stack<T>();
		for (int i = 0; i < this->items->GetLength(); i++)
			if (wfun(this->items->Get(i)))
			{
				stack->items->Append(this->items->Get(i));
			};
		return stack;
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
	void Print() const
	{
		cout << "Current queue: ";
		for (int i = 0; i < this->items->GetLength(); i++)
			cout << this->items->Get(i) << " ";
		cout << endl;
	}

	
};
