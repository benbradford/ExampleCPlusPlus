#include "test/TestCommon.h"
#include "Containers/Heap.h"

TEST(TestHeap, CanAddAndCheckGreatest)
{
	Heap<int> heap;
	heap.Add(2);
	heap.Add(1);

	ASSERT_EQ(heap.Peek(), 2);
}

TEST(TestHeap, CanAddViaIteratorAndCheckGreatest)
{
	Heap<int> heap;
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
	Heap<int, HeapGtFunc<int>> heap;
	heap.Add(2);
	heap.Add(1);

	ASSERT_EQ(heap.Peek(), 1);
}

TEST(TestHeap, CanAddAndPopInOrder)
{
	Heap<int> heap;
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
	Heap<int, HeapGtFunc<int>> heap;
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
	Heap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);

	Heap<int> h2(heap);
	ASSERT_EQ(heap.Size(), h2.Size());
	for (int i = 4; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

TEST(TestHeap, CanAssign)
{
	Heap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);

	Heap<int> h2(1);
	h2 = heap;
	ASSERT_EQ(heap.Size(), h2.Size());
	for (int i = 4; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

Heap<int> MakeTestHeap()
{
	Heap<int> heap;
	heap.Add(4);
	heap.Add(1);
	heap.Add(3);
	heap.Add(2);
	return heap;
}

TEST(TestHeap, CanMoveConstruct)
{
	
	Heap<int> h2(MakeTestHeap());
	h2.Add(5);
	for (int i = 5; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}

TEST(TestHeap, CanMoveAssign)
{
	
	Heap<int> h2(1);
	h2 = (MakeTestHeap());
	h2.Add(5);
	for (int i = 5; i > 0; --i)
	{
		ASSERT_EQ(h2.Pop(), i);
	}
}
