#pragma once

#include <assert.h>
#include <memory>
template <typename T>
struct HeapGtFunc
{
	bool operator()(const T& first, const T& second) const
	{
		return first > second;
	}
};

template <typename T>
struct HeapLtFunc
{
	bool operator()(const T& first, const T& second) const
	{
		return first < second;
	}
};

template <typename T, typename CompFunc = HeapLtFunc<T>>
class Heap
{
public:
	
	using index_t = unsigned int;
	static const auto NULL_INDEX = static_cast<index_t>(-1);
	
	Heap(unsigned int size = 32);
	Heap(const Heap& other);
	Heap(Heap&& other);
	Heap& operator=(const Heap& other);
	Heap& operator=(Heap&& other);

	template <typename Iterator>
	void Add(Iterator start, Iterator end);
	void Add(const T& value);
	const T& Peek() const;
	T Pop();
	index_t Size() const { return mSize; }

private:
	static void Swap(Heap& lhs, Heap& rhs);
	void ShiftUp(index_t node);
	void ShiftDown(index_t node);
	index_t GetParent(index_t index) const;
	index_t GetLeftChild(index_t index) const;
	index_t GetRightChild(index_t index) const;
	index_t GetMaxChild(index_t index) const;

	void Swap(index_t a, index_t b);
	unsigned int 			mMaxSize;
	CompFunc				mCompareFunction;
	std::unique_ptr<T[]>	mData;
	index_t					mSize;
};

template <typename T, typename CompFunc>
void Heap<T,CompFunc>::Swap(Heap& lhs, Heap& rhs)
{
	std::swap(lhs.mMaxSize, rhs.mMaxSize);
	std::swap(lhs.mCompareFunction, rhs.mCompareFunction);
	std::swap(lhs.mData, rhs.mData);
	std::swap(lhs.mSize, rhs.mSize);
}

template <typename T, typename CompFunc>
Heap<T,CompFunc>::Heap(unsigned int maxSize)
: mMaxSize(maxSize)
, mCompareFunction()
, mData(new T[maxSize])
, mSize(0)
{
	
}

template <typename T, typename CompFunc>
Heap<T, CompFunc>::Heap(const Heap& other)
: mMaxSize(other.mMaxSize)
, mData(new T[other.mMaxSize])
, mSize(other.mSize)
{
	for (int i=0; i < other.mSize; ++i)
	{
		mData[i] = other.mData[i];
	}
}

template <typename T, typename CompFunc>
Heap<T, CompFunc>::Heap(Heap&& other)
: mMaxSize(other.mMaxSize)
, mData(std::move(other.mData))
, mSize(other.mSize)
{
	other.mSize = 0;
}

template <typename T, typename CompFunc>
Heap<T, CompFunc>& Heap<T, CompFunc>::operator=(const Heap& other)
{
	Heap tmp(other);
	Swap(*this, tmp);
	return *this;
}

template <typename T, typename CompFunc>
Heap<T, CompFunc>& Heap<T, CompFunc>::operator=(Heap&& other)
{
	Swap(*this, other);
	return *this;
}

template <typename T, typename CompFunc>
void Heap<T, CompFunc>::Add(const T& value)
{
	assert(mSize < mMaxSize);
	mData[mSize] = value;
	ShiftUp(mSize++);
}

template <typename T, typename CompFunc>
template <typename Iterator>
void Heap<T, CompFunc>::Add(Iterator start, Iterator end)
{
	for (Iterator it = start; it != end; ++it)
	{
		Add(*it);
	}
}

template <typename T, typename CompFunc>
const T& Heap<T, CompFunc>::Peek() const
{
	assert(Size());
	return mData[0];
}

template <typename T, typename CompFunc>
T Heap<T, CompFunc>::Pop()
{
	assert(Size());
	T data = mData[0];
	--mSize;
	mData[0] = mData[mSize];
	ShiftDown(0);
	return data;
}

template <typename T, typename CompFunc>
void Heap<T, CompFunc>::ShiftUp(index_t node)
{
	auto parentIndex = GetParent(node);
	if (parentIndex == NULL_INDEX)
		return;

	if (mCompareFunction(mData[parentIndex], mData[node]))
	{
		Swap(parentIndex, node);
		ShiftUp(parentIndex);
	}
}

template <typename T, typename CompFunc>
void Heap<T, CompFunc>::ShiftDown(index_t node)
{
	
	const auto maxChild = GetMaxChild(node);
	if (maxChild != NULL_INDEX && mCompareFunction(mData[node], mData[maxChild]))
	{
		Swap(node, maxChild);
		ShiftDown(maxChild);
	}
}

template <typename T, typename CompFunc>
unsigned int Heap<T, CompFunc>::GetParent(index_t index) const
{
	return index == 0 ? NULL_INDEX : (index - 1) / 2;
}

template <typename T, typename CompFunc>
unsigned int Heap<T, CompFunc>::GetLeftChild(index_t index) const
{
	auto ret = index * 2 + 1;
	return ret >= mSize ? NULL_INDEX : ret;
}

template <typename T, typename CompFunc>
unsigned int Heap<T, CompFunc>::GetRightChild(index_t index) const
{
	auto ret = index * 2 + 2;
	return ret >= mSize ? NULL_INDEX : ret;
}

template <typename T, typename CompFunc>
unsigned int Heap<T, CompFunc>::GetMaxChild(index_t index) const
{
	const auto left = GetLeftChild(index);
	if (left == NULL_INDEX)
		return NULL_INDEX;
	if (left == mSize - 1)
		return left;
	auto right = GetRightChild(index);
	assert(right != NULL_INDEX);
	return mCompareFunction(mData[left], mData[right]) ? right : left;
}

template <typename T, typename CompFunc>
void Heap<T, CompFunc>::Swap(index_t a, index_t b)
{
	auto tmp = mData[a];
	mData[a] = mData[b];
	mData[b] = tmp;
}