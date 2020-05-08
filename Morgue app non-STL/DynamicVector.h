#pragma once

template <typename T>
class DynamicVector
{
private:
	T* elems;
	int size, capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 8);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v);
	
	// destructor
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);

	// subscript operator for the dynamic vector (can replace getter/setter)
	T& operator[](int position);

	// Adds an element to the current DynamicVector.
	void add(const T& e);

	int getSize() const;

	// delets the element on a given position
	// the position must be a valid one
	void deletePosition(int position);

	// returns the element on a given position
	// the position must be a valid one
	//T get(int position);

	// updates the element on a given position
	// the position must be a valid one
	//void set(int position, T newTElem);

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);

public:
	class Iterator
	{
	private:
		T* ptr;

	public:
		Iterator(T* pointer=NULL) : ptr{ pointer } {}
		T& operator*();
		bool operator!=(const Iterator& it);
		bool operator==(const Iterator& it);
		Iterator operator++();
		Iterator operator++(int x);
		Iterator operator--();
		Iterator operator--(int x);
	};

	typename Iterator begin(); // typename required for C++
	typename Iterator end();
};



/// Dynamic Vector methods

template <typename T>
inline DynamicVector<T>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elems = new T[capacity];
}

template <typename T>
inline DynamicVector<T>::DynamicVector(const DynamicVector<T>& v)
{
	this->size = v.size;
	this->capacity = v.capacity;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <typename T>
inline DynamicVector<T>::~DynamicVector()
{
	delete[] this->elems;
}

template <typename T>
inline DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector<T>& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->capacity = v.capacity;

	delete[] this->elems;
	this->elems = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
	return *this;
}

template <typename T>
inline T& DynamicVector<T>::operator[](int position)
{
	return this->elems[position];
}

template <typename T>
inline void DynamicVector<T>::add(const T& e)
{
	if (this->size == this->capacity)
		this->resize();
	this->elems[this->size] = e;
	this->size++;
}

template <typename T>
inline void DynamicVector<T>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	T* els = new T[this->capacity];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <typename T>
inline int DynamicVector<T>::getSize() const
{
	return this->size;
}

template <typename T>
inline void DynamicVector<T>::deletePosition(int position)
{
	for (int i = position; i < this->size - 1; i++)
		this->elems[i] = this->elems[i + 1];
	this->size--;
}
/*
template <typename T>
inline T DynamicVector<T>::get(int position)
{
	return this->elems[position];
}

template <typename T>
inline void DynamicVector<T>::set(int position, T newTElem)
{
	this->elems[position] = newTElem;
}*/


/// Iterator methods:

template <typename T>
inline typename DynamicVector<T>::Iterator DynamicVector<T>::begin()
{
	return Iterator{this->elems};
}

template <typename T>
inline typename DynamicVector<T>::Iterator DynamicVector<T>::end()
{
	return Iterator{this->elems + this->size};
}

template <typename T>
inline T& DynamicVector<T>::Iterator::operator*()
{
	return *this->ptr;
}

template <typename T>
inline bool DynamicVector<T>::Iterator::operator!=(const Iterator& it)
{
	return this->ptr != it.ptr;
}

template <typename T>
inline bool DynamicVector<T>::Iterator::operator==(const Iterator& it)
{
	return this->ptr == it.ptr;
}

template <typename T>
inline typename DynamicVector<T>::Iterator DynamicVector<T>::Iterator::operator++()
{
	this->ptr++;
	return *this;
}

template <typename T>
inline typename DynamicVector<T>::Iterator DynamicVector<T>::Iterator::operator++(int x)
{
	Iterator aux{ *this };
	this->ptr++;
	return aux;
}

template <typename T>
inline typename DynamicVector<T>::Iterator DynamicVector<T>::Iterator::operator--()
{
	this->ptr--;
	return *this;
}

template <typename T>
inline typename DynamicVector<T>::Iterator DynamicVector<T>::Iterator::operator--(int x)
{
	Iterator aux{ *this };
	this->ptr--;
	return aux;
}