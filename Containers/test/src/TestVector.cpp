#include "test/TestCommon.h"
#include "Containers/Vector.h"

TEST(TestVector, CanPushBack)
{
	Vector<int> v;
	v.PushBack(1);
	ASSERT_EQ(v[0], 1);
}

TEST(TestVector, CanPushBeyondCapacity)
{
	Vector<int> v(2);
	v.PushBack(0);
	v.PushBack(1);
	ASSERT_NO_THROW(v.PushBack(2));
	ASSERT_EQ(v.Size(),3);
}

TEST(TestVector, TestSize)
{
	Vector<int> v(2);

	for (auto i = 0u; i < 100; ++i)
	{
		v.PushBack(0);
		ASSERT_EQ(v.Size(), i+1);
	}
}

TEST(TestVector, CanInsertAtPositionZeroWhenEmpty)
{
	Vector<int> v(2);
	v.InsertAfter(0,1);
}

TEST(TestVector, CanInsertBeforeSize)
{
	Vector<int> v(10);
	for (int i=0; i < 8; ++i)
	{
		v.PushBack(i);
	}
	v.InsertAfter(5,100);
	ASSERT_EQ(v[5], 100);
	ASSERT_EQ(v[6], 5);
	ASSERT_EQ(v.Size(), 9);
}

TEST(TestVector, CanInsertAtIterator)
{
	Vector<int> v(10);
	v.InsertAfter(v.begin(),1);
	ASSERT_EQ(v[0],1);
	ASSERT_EQ(v.Size(),1);
}

TEST(TestVector, CanErase)
{
	Vector<int> v;
	v.PushBack(1);

	ASSERT_NO_THROW(v.Erase(0));
	ASSERT_EQ(v.Size(), 0);
}

TEST(TestVector, EraseWillKeepDataValid)
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);

	ASSERT_NO_THROW(v.Erase(1));
	ASSERT_EQ(v.Size(), 2);
	ASSERT_EQ(v[0],1);
	ASSERT_EQ(v[1],3);
}

TEST(TestVector, CanEraseFromIterator)
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	auto it = v.begin();
	++it;
	ASSERT_NO_THROW(v.Erase(it));
	ASSERT_EQ(v.Size(), 2);
	ASSERT_EQ(v[0],1);
	ASSERT_EQ(v[1],3);
}

TEST(TestVector, CanCopy)
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);

	Vector<int> other(v);
	ASSERT_EQ(other[0],1);
	ASSERT_EQ(other[1],2);
	ASSERT_EQ(other[2],3);
}

TEST(TestVector, CanAssign)
{
	Vector<int> v;
	Vector<int> other(1);
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);

	other = v;
	
	ASSERT_EQ(other[0],1);
	ASSERT_EQ(other[1],2);
	ASSERT_EQ(other[2],3);
}

Vector<int> CreateV()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	return v;
}

TEST(TestVector, CanMove)
{
	Vector<int> other(CreateV());
	ASSERT_EQ(other[0],1);
	ASSERT_EQ(other[1],2);
	ASSERT_EQ(other[2],3);
}

TEST(TestVector, CanMoveAssign)
{
	Vector<int> other(1);
	other = CreateV();
	
	ASSERT_EQ(other[0],1);
	ASSERT_EQ(other[1],2);
	ASSERT_EQ(other[2],3);
}

