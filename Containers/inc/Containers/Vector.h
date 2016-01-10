#pragma once

template <typename T>
class Vector
{
public:
	struct Iterator
	{
	public:
		
		T& operator*() { return value;}

		bool operator==(const Iterator& other) const
		{
			return index == other.index;
		}

		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}

		Iterator operator++()
		{
			if (index++ >= vec.mCapacity-1)
			{
				value = nullptr;
			}
			else 
			{
				value = &vec.mData[index];
			}
			return *this;
		}
	private:
		Iterator(T* v, unsigned int i, Vector& vc)
		: value(v), index(i), vec(vc){}
		T* value;
		unsigned int index;
		Vector& vec;
		friend class Vector;
	};

	Vector(unsigned int initialCapacity = 8)
	: mCapacity(initialCapacity)
	, mSize(0)
	, mData(new T[initialCapacity])
	{}

	Vector(const Vector& other)
	: mCapacity(other.mCapacity)
	, mSize(other.mSize)
	, mData(new T[other.mCapacity])
	{
		for (auto i = 0u; i < mSize; ++i)
		{
			mData[i] = other.mData[i];
		}
	}

	Vector& operator=(const Vector& other)
	{
		Vector c(other);
		swap(c, *this);
		return *this;
	}

	Vector(Vector&& other) = default;
	Vector& operator=(Vector&& other) = default;

	// :TODO: add move
	void PushBack(const T& value)
	{
		if (mSize == mCapacity)
		{
			Grow(mCapacity + (mCapacity/2));
			PushBack(value);
			return;
		}
		mData[mSize++] = value;
	}
	void InsertAfter(unsigned int position, const T& value)
	{
		if (mSize == mCapacity)
		{
			Grow(mCapacity + (mCapacity/2));
			InsertAfter(position, value);
			return;
		}
		for (int i = int(++mSize); i > position; --i)
		{
			mData[i] = mData[i-1];
		}
		mData[position] = value;
	}
	void InsertAfter(const Iterator& it, const T& value) { InsertAfter(it.index, value);}
	void Erase(unsigned int position)
	{
		for (int i=position; i < mSize; ++i)
		{
			std::swap(mData[i], mData[i+1]);
		}
		mData[mSize--] = T{};
	}
	T const*const GetRaw() const { return mData.get(); }
	void Erase(const Iterator& it) { Erase(it.index);}
	T& operator[](unsigned int index) { return mData[index];}

	unsigned int Size() const { return mSize; }
	unsigned int Capacity() const { return mCapacity; }

	Iterator begin() { return Iterator{&mData[0],0,*this};}
	Iterator end() { return Iterator{nullptr, mCapacity,*this};}
	
	static void swap(Vector& lhs, Vector& rhs)
	{
		std::swap(lhs.mCapacity, rhs.mCapacity);
		std::swap(lhs.mSize, rhs.mSize);
		std::swap(lhs.mData, rhs.mData);
	}
private:
	unsigned int mCapacity;
	unsigned int mSize;
	std::unique_ptr<T[]> mData;	

	void Grow(unsigned int newCapacity)
	{
		Vector next(newCapacity);
		for (unsigned int i=0; i < mSize; ++i)
		{
			next.mData[i] = mData[i];
		}
		next.mSize = mSize;
		swap(*this,next);
	}
};