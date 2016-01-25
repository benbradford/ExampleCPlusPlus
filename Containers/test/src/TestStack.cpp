#include "test/TestCommon.h"
#include "Containers/Stack.h"

TEST(TestStack, CanPush)
{
	Stack<int> s;
	ASSERT_NO_THROW(s.Push(0));
}


TEST(TestStack, CanPeek)
{
	Stack<int> s;
	s.Push(99);
	ASSERT_NO_THROW(s.Peek());
	ASSERT_EQ(s.Peek(), 99);
}

TEST(TestStack, CanPop)
{
	Stack<int> s;
	s.Push(0);
	ASSERT_NO_THROW(s.Pop());
}

TEST(TestStack, CanPushMany)
{
	Stack<int> s;
	for (int i=0; i < 10; ++i)
		ASSERT_NO_THROW(s.Push(i));
}

TEST(TestStack, CanPeekAndPopMany)
{
	Stack<int> s;
	for (int i=0; i < 10; ++i)
		s.Push(i);
	for (int i = 9; i > 0; --i)
	{
		ASSERT_NO_THROW(s.Peek());
		ASSERT_EQ(s.Peek(), i);
		ASSERT_NO_THROW(s.Pop());
	}
}

TEST(TestStack, PeekOnEmptyWillThrow)
{
	Stack<int> s;
	ASSERT_THROW(s.Peek(), PeekWhenEmptyException);
	s.Push(0);
	s.Pop();
	ASSERT_THROW(s.Peek(), PeekWhenEmptyException);
}

TEST(TestStack, PopOnEmptyWillThrow)
{
	Stack<int> s;
	ASSERT_THROW(s.Pop(), PopWhenEmptyException);
	s.Push(0);
	s.Pop();
	ASSERT_THROW(s.Pop(), PopWhenEmptyException);
}

TEST(TestStack, SizeWorks)
{
	Stack<int> s;
	ASSERT_EQ(s.Size(),0);
	s.Push(1);
	ASSERT_EQ(s.Size(),1);
	s.Pop();
	ASSERT_EQ(s.Size(),0);
}

TEST(TestStack, CanCopy)
{
	Stack<int> s;
	for (int i=0; i < 10; ++i)
		s.Push(i);
	Stack<int> c(s);
	ASSERT_EQ(c.Size(),s.Size());
	for (int i=9; i >=0; --i)
	{
		ASSERT_EQ(c.Peek(), i);
		c.Pop();
	}
}

TEST(TestStack, CanAssign)
{
	Stack<int> s;
	for (int i=0; i < 10; ++i)
		s.Push(i);
	Stack<int> c;
	c = s;
	ASSERT_EQ(c.Size(),s.Size());
	for (int i=9; i >=0; --i)
	{
		ASSERT_EQ(c.Peek(), i);
		c.Pop();
	}
}

Stack<int> CreateStackOfInts(int amount)
{
	Stack<int> s;
	for (int i=0; i < 10; ++i)
		s.Push(i);
	return s;
}

TEST(TestStack, CanMove)
{
	Stack<int> c(CreateStackOfInts(10));
	ASSERT_EQ(c.Size(),10);
	for (int i=9; i >=0; --i)
	{
		ASSERT_EQ(c.Peek(), i);
		c.Pop();
	}
}

TEST(TestStack, CanMoveAssign)
{
	Stack<int> c;
	c = CreateStackOfInts(10);
	ASSERT_EQ(c.Size(),10);
	for (int i=9; i >=0; --i)
	{
		ASSERT_EQ(c.Peek(), i);
		c.Pop();
	}
}

struct BigCtorThrow{};
struct BigCopyThrow{};
struct BigAssignThrow{};
struct BigMoveThrow{};
struct BigMoveAssignThrow{};

struct Big
{

public:
	struct Throws
	{
		friend class ThrowsHandle;
		bool shouldThrowWhenCopiedFrom = false;
		bool shouldThrowWhenAssignedFrom = false;
		bool shouldThrowWhenMoveFrom = false;
		bool shouldThrowWhenMoveAssignedFrom = false;
		void reset()
		{
			Throws t = Throws{};
			*this = t;
		}
	};
private:	
	static Throws throws;
	friend class ThrowsHandle;
public:
	struct ThrowsHandle
	{
		Throws& get() const{return Big::throws;}

		~ThrowsHandle()
		{
			Big::throws.reset();
		}
	};

	char* data;
	int index;

	~Big()
	{
		if (data)
			delete [] data;
	}
	Big(int i, bool dothrow = false)
		: data(new char[256]), index(i)
		{
			if (dothrow)
				throw BigCtorThrow{};
		}
	Big(const Big& other)
		: data(new char[256]), index(other.index)
	{
		printf("copy\n");
		if (throws.shouldThrowWhenCopiedFrom)
		{
			delete []data;
			data = nullptr;
			throw BigCopyThrow{};
		}
	}

	Big const& operator=(const Big& other)
	{
		printf("assign\n");
		data = new char[256];
		index = other.index;
		if (throws.shouldThrowWhenAssignedFrom)
		{
			delete [] data;
			data = nullptr;
			throw BigAssignThrow{};
		}
		return *this;
	}

	Big(Big&&other)
	: data(std::move(other.data))
	, index(other.index)
	{
		printf("move\n");
		if (throws.shouldThrowWhenMoveFrom)
		{
			throw BigMoveThrow{};
		}
		other.data = nullptr;
	}

	Big const& operator=(Big&&other)
	{
		printf("moveassign\n");
		data = std::move(other.data);
		index =other.index;
		if (throws.shouldThrowWhenMoveAssignedFrom)
		{
			throw BigMoveAssignThrow{};
		}
		other.data = nullptr;
		return *this;
	}

};
Big::Throws Big::throws{};

Stack<Big> CreateBigStack()
{
	Stack<Big> big;
	big.Push(Big{1});
	return big;
}

TEST(TestStack, CanUseWithBigData)
{
	Stack<Big> bigstack;
	auto handle = Big::ThrowsHandle();
	ASSERT_NO_THROW(bigstack.Push(Big{1}));
	ASSERT_NO_THROW(bigstack.Peek());
	ASSERT_EQ(bigstack.Peek().index,1);
	ASSERT_EQ(bigstack.Size(),1);
	ASSERT_NO_THROW(bigstack.Pop());
}

TEST(TestStack, CanAvoidCopyBigData)
{
	Stack<Big> bigstack;
	auto handle = Big::ThrowsHandle();
	handle.get().shouldThrowWhenCopiedFrom = true;

	ASSERT_NO_THROW(bigstack.Push(Big{1}));
	ASSERT_NO_THROW(bigstack.Peek());
	ASSERT_NO_THROW(bigstack.Pop());
}

TEST(TestStack, CanAvoidAssignBigData)
{
	Stack<Big> bigstack;
	auto handle = Big::ThrowsHandle();
	handle.get().shouldThrowWhenAssignedFrom = true;

	ASSERT_NO_THROW(bigstack.Push(Big{1}));
	ASSERT_NO_THROW(bigstack.Peek());
	ASSERT_NO_THROW(bigstack.Pop());

}

TEST(TestStack, PushBigWillMove)
{
	Stack<Big> bigstack;
	auto handle = Big::ThrowsHandle();
	handle.get().shouldThrowWhenMoveFrom = true;
	ASSERT_THROW(bigstack.Push(Big{1}), BigMoveThrow);
}

TEST(TestStack, CopyBigCallsCopyCtor)
{
	Stack<Big> bigstack;
	auto handle = Big::ThrowsHandle();
	bigstack.Push(Big{1});
	handle.get().shouldThrowWhenCopiedFrom = true;
	ASSERT_THROW(Stack<Big> other(bigstack), BigCopyThrow);	
}

TEST(TestStack, ExceptionInAssignOfBigLeavesObjectInEmptyState)
{
	Stack<Big> bigstack;
	auto handle = Big::ThrowsHandle();
	bigstack.Push(Big{1});
	Stack<Big> other;
	other.Push(Big{2});
	bool thrown = false;
	try
	{
		handle.get().shouldThrowWhenCopiedFrom = true;
		other = bigstack; 
	}
	catch(BigCopyThrow)
	{
		thrown = true;
		handle.get().reset();
		ASSERT_EQ(other.Size(),1);
		ASSERT_NO_THROW(other.Push(Big{1}));
		ASSERT_EQ(other.Size(),2);
		ASSERT_NO_THROW(other.Peek());
		ASSERT_NO_THROW(other.Pop()); 
		ASSERT_NO_THROW(other.Peek());
		ASSERT_EQ(other.Size(),1);
		ASSERT_NO_THROW(other.Pop());
		ASSERT_EQ(other.Size(),0);
	}
	catch(...)
	{
		ASSERT_EQ(true,false);
	}
	ASSERT_EQ(thrown, true);
}

TEST(TestStack, ExceptionInMoveAssignOfBigLeavesObjectInEmptyState)
{
	auto handle = Big::ThrowsHandle();
	Stack<Big> other;
	other.Push(Big{2});
	bool thrown = false;
	try
	{
		handle.get().shouldThrowWhenMoveFrom = true;
		other = CreateBigStack(); 
	}
	catch(BigMoveThrow)
	{
		thrown = true;
		handle.get().reset();
		ASSERT_EQ(other.Size(),1);
		ASSERT_NO_THROW(other.Push(Big{1}));
		ASSERT_EQ(other.Size(),2);
		ASSERT_NO_THROW(other.Peek());
		ASSERT_NO_THROW(other.Pop()); 
		ASSERT_NO_THROW(other.Pop());
		ASSERT_EQ(other.Size(),0);
	}
	catch(...)
	{
		ASSERT_EQ(true,false);
	}
	ASSERT_EQ(thrown, true);
}