#include "test/TestCommon.h"
#include "Containers/Heap.h"

TEST(TestHeap, CanAddAndCheckGreatest)
{
	MaxHeap<int> heap;
	heap.Add(2);
	heap.Add(1);

	ASSERT_EQ(heap.Peek(), 2);
}

TEST(TestHeap, CanAddViaIteratorAndCheckGreatest)
{
	MaxHeap<int> heap;
	std::vector<int> num = {5,2,3,1,4};
	heap.Add(num.begin(), num.end());
	ASSERT_EQ(heap.Size(), 5);
	ASSERT_EQ(heap.Peek(), 5);
	for (int i = 5; i > 0; --i)
	{
		ASSERT_EQ(heap.Pop(), i);
	}
}

TEST(TestHeap, CanAddAndCheckLowest)
{
	MinHeap<int> heap;
	heap.Add(2);
	heap.Add(1);

	ASSERT_EQ(heap.Peek(), 1);
}

TEST(TestHeap, CanAddAndPopInOrder)
{
	MaxHeap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);

	for (int i = 4; i > 0; --i)
	{
		ASSERT_EQ(heap.Pop(), i);
	}
}

TEST(TestHeap, CanAddAndPopInOrderMinHeap)
{
	MinHeap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);

	for (int i = 1; i <= 4; ++i)
	{
		ASSERT_EQ(heap.Pop(), i);
	}
}

TEST(TestHeap, CanCopy)
{
	MaxHeap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);

	MaxHeap<int>h2(heap);
	ASSERT_EQ(heap.Size(), h2.Size());
	for (int i = 4; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

TEST(TestHeap, CanAssign)
{
	MaxHeap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);

	MaxHeap<int>h2(1);
	h2 = heap;
	ASSERT_EQ(heap.Size(), h2.Size());
	for (int i = 4; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

MaxHeap<int>MakeTestHeap()
{
	MaxHeap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);
	return heap;
}

TEST(TestHeap, CanMoveConstruct)
{
	
	MaxHeap<int>h2(MakeTestHeap());
	h2.Add(5);
	for (int i = 5; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

TEST(TestHeap, CanMoveAssign)
{
	
	MaxHeap<int>h2(1);
	h2 = (MakeTestHeap());
	h2.Add(5);
	for (int i = 5; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

struct HeapTest
{
	static int newDeleteCalls;
	HeapTest()
	: data(nullptr)
	, index(-1)
	{

	}
	HeapTest(int i)
	: data(new char[256])
	, index(i)
	{
		++newDeleteCalls;
	}
	~HeapTest()
	{
		if (data)
		{
			delete [] data;
			assert(index != -1); // ensuring no wasted data
			--newDeleteCalls;
		}
	}

	HeapTest(const HeapTest& other) = delete;
	HeapTest& operator=(const HeapTest& other) = delete;

	HeapTest(HeapTest&& other)
	: data(other.data)
	, index(other.index)
	{
		other.data = nullptr;
	}

	
	HeapTest& operator=( HeapTest&& other)
	{
		swap(*this,other);
		return *this;
	}

	static void swap(HeapTest& lhs, HeapTest& rhs)
	{
		std::swap(lhs.data, rhs.data);
		std::swap(lhs.index, rhs.index);
	}

	bool operator>(const HeapTest& other) const { return index > other.index;}
	bool operator<(const HeapTest& other) const { return index < other.index;}

	const char* data;
	int index;
};

int HeapTest::newDeleteCalls(0);

TEST(TestHeap, CanUseHeapWithBigData)
{

	Heap<HeapTest> heap;
	heap.Add(HeapTest(3));
	heap.Add(HeapTest(1));
	heap.Add(HeapTest(2));
	for (int i = 3; i > 0; --i)
	{
		auto d = heap.Pop();
		ASSERT_EQ(d.index, i);
	}

ASSERT_EQ(HeapTest::newDeleteCalls , 0);

}

Heap<HeapTest> CreateHeapTestHeap()
{

	Heap<HeapTest> heap;
	heap.Add(HeapTest(3));
	heap.Add(HeapTest(1));
	heap.Add(HeapTest(2));
	return heap;
}

TEST(TestHeap, CanMoveBigHeapData)
{
	Heap<HeapTest> heap = CreateHeapTestHeap();
	for (int i = 3; i > 0; --i)
	{
		auto d = std::move(heap.Pop());
		ASSERT_EQ(d.index, i);
	}
	ASSERT_EQ(HeapTest::newDeleteCalls , 0);
}

TEST(TestHeap, CanMoveAssignBigHeapData)
{
	Heap<HeapTest> heap;
	heap = CreateHeapTestHeap();
	for (int i = 3; i > 0; --i)
	{
		HeapTest d = std::move(heap.Pop());
		ASSERT_EQ(d.index, i);
	}
	ASSERT_EQ(HeapTest::newDeleteCalls , 0);
}



