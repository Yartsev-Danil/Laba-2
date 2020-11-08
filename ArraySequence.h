#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class ArraySequence :public Sequence<T>
{
private:
	DynamicArray<T>* data;
	int count;
public:
	ArraySequence(const int count = 0) : count(0)
	{
		int actualCount = count > 0 ? count : 1;
		
		this->data = new DynamicArray<T>(actualCount);
	}
	ArraySequence(T* items, int count) {
		if (!items || count <= 0)
			throw std::logic_error("no items or count error");
		this->count = count;
		this->data = new DynamicArray<T>(items, count);
	}
	ArraySequence(const ArraySequence<T>& other) {
		if (!other.count || !other.data)
			throw std::logic_error("no items or count error");
		this->count = other.count;
		this->data = new DynamicArray<T>(*(other.data));
	}
public:
	bool TryGetValue(const int index, T& value) const;
	virtual T GetLength() const override
	{
		return this->data->GetSize();
	}
	virtual T GetFirst() const override
	{
		if (this->data->HasValue(0))
			return this->data->Get(0);
		throw std::logic_error("no items");
	}
	virtual T GetLast() const override 
	{
		if (this->count <= 0 || !this->data)
			throw std::out_of_range("index out of range");
		if (this->data->HasValue(this->count - 1))
			return this->data->Get(this->count - 1);
		throw std::logic_error("no value");
	}
	virtual T Get(const int i) const override 
	{
		if (this->count <= 0 || !this->data)
			throw std::out_of_range("index out of range");
		if (this->data->HasValue(i))
			return this->data->Get(i);
		throw std::logic_error("no value");
	}
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const override
	{
		if (start < 0 || start > end || end >= this->count || !this->count || !this->data)
			throw std::out_of_range("index out of range");
		ArraySequence<T>* subseq = new ArraySequence<T>(end - start + 1);
		subseq->count = end - start + 1;
		for (int i = start; i <= end; i++)
		{
			subseq->data->Set(i - start, this->data->Get(i));
		};
		return subseq;
	}
public:
	virtual void Append(T value) override
	{
		if (!this->count || !this->data)
			throw std::out_of_range("index out of range");
		this->count++;
		this->data->Resize(this->count);
		this->data->Set(this->count - 1, value);
	}
	virtual void Prepend(T value) override
	{
		if (!this->count || !this->data)
			throw std::out_of_range("index out of range");
		this->count++;
		DynamicArray<T>* array = new DynamicArray<T>(this->count);
		array->Set(0, value);
		for (int i = 1; i < this->count; i++)
		{
			if (this->data->HasValue(i))
				array->Set(i, this->data->Get(i - 1));
		};
		this->data->~DynamicArray();
		this->data = array;
	}
	virtual void Set(const int index, const T value) override
	{
		if (index < 0 || index >= this->count || !this->count || !this->data)
			throw std::out_of_range("index out of range");
		this->data->Set(index, value);
	};
	virtual void InsertAt(const int index, T value) override
	{
		if (index < 0 || index > this->count || !this->count || !this->data)
			throw std::out_of_range("index out of range");
		DynamicArray<T>* array = new DynamicArray<T>(this->count + 1);
		for (int i = 0; i < index; i++)
		{
			if (this->data->HasValue(i))
				array->Set(i, this->data->Get(i));
		};
		array->Set(index, value);
		for (int i = index; i < this->count; i++)
		{
			if (this->data->HasValue(i))
				array->Set(i + 1, this->data->Get(i));
		};
		this->count++;
		this->data->~DynamicArray();
		this->data = array;
	}
	virtual void RemoveAt(const int index) override
	{
		if (index < 0 || index >= this->count || !this->count || !this->data)
			throw std::out_of_range("index out of range");
		DynamicArray<T>* array = new DynamicArray<T>(this->count - 1);
		for (int i = 0; i < index; i++)
		{
			array->Set(i, this->data->Get(i));
		};
		for (int i = index + 1; i < this->count; i++)
		{
			array->Set(i - 1, this->data->Get(i));
		};
		this->count--;
		this->data->~DynamicArray();
		this->data = array;
	}
	virtual void Remove(T value) override // Удаляет первое вхождение value
	{
		if (!this->count || !this->data)
			throw std::out_of_range("index out of range");
		int index = -1;
		for (int i = 0; i < this->count; i++)
		{
			if (this->data->HasValue(i) && this->data->Get(i) == value)
			{
				index = i;
				this->RemoveAt(index);
				break;
			};
		};
		if (index == -1)
			throw std::logic_error("there is not value of argument");
	} 
	virtual void RemoveAll(T value) override 
	{
		if (!this->count || !this->data)
			throw std::out_of_range("index out of range");
		int flag = 0;
		int j = 0;
		int num = this->count;
		for (int i = 0; i < num; i++)
		{
			if (this->data->HasValue(i) && this->data->Get(j) == value)
			{
				flag = 1;
				this->RemoveAt(j);
			}
			else { j++; };
		};
		if (!flag)
			throw std::logic_error("there is not value of argument");
	}
	
	virtual Sequence<T>* Concat(const Sequence<T>& other) const override
	{
		if (!this->count || !this->data || !other.GetLength())
			throw std::out_of_range("index out of range");
		ArraySequence<T>* seq = new ArraySequence<T>(this->count + other.GetLength());
		seq->count = this->count + other.GetLength();
		int index = 0;
		for (index; index < this->count; index++)
		{
			seq->Set(index, this->data->Get(index));
		};
		for (int i = 0; i < other.GetLength(); i++)
		{
			seq->Set(index, other.Get(i));
			index++;
		};
		return seq;
	}
	virtual Sequence<T>* Copy() const override
	{
		Sequence<T>* seq = new ArraySequence<T>(*this);
		return seq;
	};
	virtual void CopyTo(Sequence<T>* target, const int startIndex) const override
	{
		if (!target->GetLength() || !target || startIndex < 0 || startIndex >= target->GetLength())
			throw std::out_of_range("index out of range");
		for (int i = startIndex, index = 0; i < target->GetLength() && index < this->count; i++, index++)
		{
			target->Set(i, this->data->Get(index));
		}
	}
public:
	~ArraySequence() {delete this->data;}
};
template <class T>
bool ArraySequence<T> ::TryGetValue(const int index, T& value) const
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
	if (!this->data->HasValue(index))
		return false;
	value = this->data->Get(index);
	return true;
}
