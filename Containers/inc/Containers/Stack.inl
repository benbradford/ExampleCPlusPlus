
template <typename T>
Stack<T>::Stack()
: mSize(0)
{

}

template <typename T>
Stack<T>::Stack(const Stack& other)
: mSize(0)
{
	if (other.mSize == 0)
	{
		return;
	}

	CopyTo(other.mTop.get());
	mSize = other.mSize;
}

template <typename T>
Stack<T>::Stack(Stack&& other)
: mSize(0)
{
	if (other.mSize == 0)
	{
		return;
	}

	MoveTo(std::move(other.mTop));
	mSize = other.mSize;
	other.mSize = 0;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
	printf("stack assign\n");
	if (other.mSize == 0)
	{
		mTop.reset(nullptr);
		mSize = 0;
		return *this;
	}

	CopyTo(other.mTop.get());
	mSize = other.mSize;
	return *this;
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other)
{
	if (other.mSize == 0)
	{
		mTop.reset(nullptr);
		mSize = 0;
		return *this;
	}

	MoveTo(std::move(other.mTop));
	mSize = other.mSize;
	return *this;
}

template <typename T>
void Stack<T>::CopyTo(Data* node)
{
	if(node->mBelow.get())
	{
		CopyTo(node->mBelow.get());
	}
	auto newTop = std::make_unique<Data>(node->mValue);
	newTop->mBelow = std::move(mTop);
	mTop = std::move(newTop);
}

template <typename T>
void Stack<T>::MoveTo(std::unique_ptr<Data> node)
{
	if(node->mBelow.get())
	{
		MoveTo(std::move(node->mBelow));
	}

	auto newTop = std::make_unique<Data>(std::move(node->mValue));
	newTop->mBelow = std::move(mTop);
	mTop = std::move(newTop);
}

template <typename T>
void Stack<T>::Push(const T& t)
{
	mTop = std::make_unique<Data>(t, std::move(mTop));
	++mSize;
}

template <typename T>
void Stack<T>::Push(T&& t)
{
	mTop = std::make_unique<Data>(std::forward<T>(t), std::move(mTop));
	++mSize;
}

template <typename T>
T& Stack<T>::Peek()
{
	if (mSize == 0)
		throw PeekWhenEmptyException{};
	return mTop->mValue;
}

template <typename T>
const T& Stack<T>::Peek() const
{
	if (mSize == 0)
		throw PeekWhenEmptyException{};
	return mTop->mValue;
}

template <typename T>
void Stack<T>::Pop()
{
	if (mSize == 0)
		throw PopWhenEmptyException{};
	mTop = std::move(mTop->mBelow);
	--mSize;
}

template <typename T>
Stack<T>::Data::Data( const T& value, std::unique_ptr<Data> below)
: mValue(value)
, mBelow(std::move(below))
{

}

template <typename T>
Stack<T>::Data::Data(T&& value, std::unique_ptr<Data> below)
: mValue(std::move(value))
, mBelow(std::move(below))
{

}

template <typename T>
Stack<T>::Data::Data(const T& value)
: mValue(value)
{

}

template <typename T>
Stack<T>::Data::Data(T&& value)
: mValue(std::move(value))
{

}