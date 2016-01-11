#include "test/TestCommon.h"
#include "Containers/BinaryTree.h"

TEST(TestBinaryTree, CanAdd)
{
	BinaryTree<int> t;
	t.Add(5);
	ASSERT_EQ(*t.begin(), 5);
}

TEST(TestBinaryTree, CanAddSeveral)
{
	BinaryTree<int> t;
	t.Add(3);
	t.Add(5);
	t.Add(1);
	t.Add(6);
	t.Add(2);
	t.Add(4);
	t.Add(0);
	t.Add(7);
	t.Add(8);
	ASSERT_EQ(t.Size(), 9);
}

TEST(TestBinaryTree, CanIterate)
{
	BinaryTree<int> t;
	t.Add(3);
	t.Add(5);
	t.Add(1);
	t.Add(6);
	t.Add(2);
	t.Add(4);
	t.Add(0);
	t.Add(7);
	t.Add(8);
	t.Add(15);
	t.Add(14);
	int count = 0;
	for (auto v : t)
	{
		if (count <= 8)
		{
			ASSERT_EQ(v, count);
			
		}
		count++;
	}
	ASSERT_EQ(count, 11);
}

TEST(TestBinaryTree, CanIterateWhenOnlyOne)
{
	BinaryTree<int> t;
	t.Add(3);
	int count = 0;
	for (auto v : t)
	{
		ASSERT_EQ(v, 3);
		count++;
	}
	ASSERT_EQ(count, 1);
}

TEST(TestBinaryTree, IterateWhenNoneWontIterate)
{
	BinaryTree<int> t;
	int count = 0;
	for (auto v : t)
	{
		count++;
	}
	ASSERT_EQ(count, 0);
}