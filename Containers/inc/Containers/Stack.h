#pragma once

#include <memory>

struct PopWhenEmptyException{};
struct PeekWhenEmptyException{};

template <typename T>
class Stack
{
public:
	
	Stack();
	~Stack() noexcept = default;
	Stack(const Stack&);
	Stack(Stack&&);
	Stack& operator=(const Stack&);
	Stack& operator=(Stack&&);

	void Push(const T&);
	void Push(T&&);
	T&   Peek();
	const T&   Peek() const;
	void Pop();
	unsigned int Size() const noexcept{ return mSize; }
private:
	struct Data
	{
		T mValue;
		std::unique_ptr<Data> mBelow;

		Data(const T& value);
		Data(T&& value);
	};
	
	void CopyTo(Data* node);
	void MoveTo(std::unique_ptr<Data> node);
	
	std::unique_ptr<Data> mTop;
	unsigned int mSize;
};
