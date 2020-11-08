#pragma once



template <class T>
class Optional
{
private:
	static Optional<T>* empty;
	static bool emptyIsSet;
public:
	static Optional<T>* Empty()
	{
		if (!emptyIsSet) {
			empty = new Optional<T>();
			emptyIsSet = true;
		}
		return empty;
	}
private:
	T value;
	bool hasValue;
public:
	Optional(T value)
	{
		this->value = value;
		this->hasValue = true;
	}
private:
	Optional()
	{
		this->hasValue = false;
	}
public:
	T GetValue() const
	{
		if (this->hasValue)
			return this->value;
		else
			throw std::logic_error("element is empty");// Invalid Operation Exception
	}
	bool HasValue() const { return this->hasValue; }
	bool TryGetValue(T& value) const
	{
		if (!this->hasValue)
			return false;
		value = this->value;
		return true;
	}
	void Set(T value)
	{
		this->value = value;
	}
	void SetHasValue(bool hasvalue) 
	{
		this->hasValue = hasvalue;
	}
public:
	bool operator==(Optional<T>& other)
	{
		return this->hasValue == other.hasValue && (!this->hasValue || this->value == other.value);
	}
	operator T() const
	{
		if (!this->hasValue)
			return false;
		return this->value;
	}
};
