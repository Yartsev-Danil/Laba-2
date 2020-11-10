#pragma once

#include "Sequence.hpp"
#include "DynamicArray.hpp"

template <class T>
class ArraySequence : public Sequence<T>
{
private:
	DynamicArray<T>* data;
	int count;
public:
	ArraySequence(T* items, const int count);
	ArraySequence(const int count = 0);
	ArraySequence(const ArraySequence<T>& other);
public:
	virtual int GetLength() const override { return this->count; };
	virtual T GetFirst() const override;
	virtual T GetLast() const override;
	virtual T Get(const int i) const override;
	virtual Sequence<T>* GetSubsequence(const int start, const int end) const override;
	bool HasValue(const int index) const;
	bool TryGetValue(const int index, T& value) const;
public:
	virtual void Append(const T value) override;
	virtual void Prepend(const T value) override;
	virtual void Set(const int index, const T value) override;
	virtual void InsertAt(const int index, const T value) override;
	virtual void RemoveAt(const int index) override;
	virtual void Remove(const T value) override;
	virtual void RemoveAll(const T value) override;
	virtual Sequence<T>* Copy() const override
	{
		Sequence<T>* seq = new ArraySequence<T>(*this);
		return seq;
	};
	virtual Sequence<T>* Concat(const Sequence<T>& other) const override;
	virtual void CopyTo(Sequence<T>* target, const int startIndex) const override;
public:
	~ArraySequence()
	{
		delete this->data;
	};
};

/////////////////////////////////////////////////////

template <class T>
ArraySequence<T> ::ArraySequence(T* items, const int count)
{
	if (!items || count <= 0)
		throw OperationError();
	this->count = count;
	this->data = new DynamicArray<T>(items, count);
};

template <class T>
ArraySequence<T> ::ArraySequence(const int count)
{
	int actualCount = count > 0 ? count : 1;
	this->count = actualCount;
	this->data = new DynamicArray<T>(actualCount);
};

template <class T>
ArraySequence<T> ::ArraySequence(const ArraySequence<T>& other)
{
	if (!other.count || !other.data)
		throw OperationError();
	this->count = other.count;
	this->data = new DynamicArray<T>(*(other.data));
};

template <class T>
T ArraySequence<T> ::GetFirst() const
{
	if (this->count <= 0 || !this->data)
		throw IndexOutOfRange(1);
	if (this->data->HasValue(0))
		return this->data->Get(0);
	throw NoneValue(1);
};

template <class T>
T ArraySequence<T> ::GetLast() const
{
	if (this->count <= 0 || !this->data)
		throw IndexOutOfRange(1);
	if (this->data->HasValue(this->count - 1))
		return this->data->Get(this->count - 1);
	throw new NoneValue(1); 
};

template <class T>
T ArraySequence<T> ::Get(const int i) const
{
	if (i < 0 || i >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
	if (this->data->HasValue(i))
		return this->data->Get(i);
	throw NoneValue(1);
};

template <class T>
bool ArraySequence<T> ::HasValue(const int index) const
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
	return this->data->HasValue(index);
}


template <class T>
bool ArraySequence<T> :: TryGetValue(const int index, T& value) const
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
	if (!this->data->HasValue(index))
		return false;
	value = this->data->Get(index);
	return true;
}


template <class T>
Sequence<T>* ArraySequence<T> ::GetSubsequence(const int start, const int end) const
{
	if (start < 0 || start > end || end >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
	ArraySequence<T>* subseq = new ArraySequence<T>(end - start + 1);
	subseq->count = end - start + 1;
	for (int i = start; i <= end; i++)
	{
		subseq->data->Set(i - start, this->data->Get(i));
	};
	return subseq;
};

template <class T>
void ArraySequence<T> ::Prepend(const T value)
{
	if (!this->count || !this->data)
		throw IndexOutOfRange(1);
	this->count++;
	DynamicArray<T>* array = new DynamicArray<T>(this->count);
	array->Set(0, value);
	for (int i = 1; i < this->count; i++)
	{
		if(this->data->HasValue(i - 1))
			array->Set(i, this->data->Get(i - 1));
	};
	this->data->~DynamicArray();
	this->data = array;
};

template <class T>
void ArraySequence<T> ::Append(const T value)
{
	if (!this->count || !this->data)
		throw IndexOutOfRange(1);
	this->count++;
	this->data->Resize(this->count);
	this->data->Set(this->count - 1, value);
};

template <class T>
void ArraySequence<T> ::Set(const int index, const T value)
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1); 
	this->data->Set(index, value);
};

template <class T>
void ArraySequence<T> ::InsertAt(const int index, const T value)
{
	if (index < 0 || index > this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
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
};

template <class T>
void ArraySequence<T> ::RemoveAt(const int index)
{
	if (index < 0 || index >= this->count || !this->count || !this->data)
		throw IndexOutOfRange(1);
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
};

template <class T>
void ArraySequence<T> ::Remove(const T value)
{
	if (!this->count || !this->data)
		throw IndexOutOfRange(1);
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
		throw NoneValue(2);
};

template <class T>
void ArraySequence<T> ::RemoveAll(const T value)
{
	if (!this->count || !this->data)
		throw IndexOutOfRange(1);
	int flag = 0;
	int j = 0;
	int num = this->count;
	for (int i = 0; i < num; i++)
	{
		if (this->data->HasValue(j) && this->data->Get(j) == value)
		{
			flag = 1;
			this->RemoveAt(j);
		}
		else { j++; };
	};
	if (!flag)
		throw NoneValue(2);
};

template <class T>
Sequence<T>* ArraySequence<T> ::Concat(const Sequence<T>& other) const
{
	if (!this->count || !this->data || !other.GetLength())
		throw IndexOutOfRange(1);
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
};

template <class T>
void ArraySequence<T> ::CopyTo(Sequence<T>* target, const int startIndex) const
{
	if (!target->GetLength() || !target || startIndex < 0 || startIndex >= target->GetLength())
		throw IndexOutOfRange(1);
	for (int i = startIndex, index = 0; i < target->GetLength() && index < this->count; i++, index++)
	{
		target->Set(i, this->data->Get(index));
	};
}
