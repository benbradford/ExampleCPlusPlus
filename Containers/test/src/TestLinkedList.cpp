#include "test/TestCommon.h"
#include "Containers/LinkedList.h"

TEST(TestLinkedList, CanPushBack)
{
	LinkedList<int> l;
	ASSERT_NO_THROW(l.PushBack(0));
}

TEST(TestLinkedList, CanGetBegin)
{
	LinkedList<int> l;
	l.PushBack(0);
	ASSERT_EQ(l.begin().value, 0);
}

TEST(TestLinkedList, CanCompareWithEnd)
{
	LinkedList<int> l;
	l.PushBack(100);
	ASSERT_NE(l.begin().value, l.end().value);
	ASSERT_EQ(l.end(), l.end());
}

TEST(TestLinkedList, CanCopy)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	LinkedList<int> l2(l);
	ASSERT_EQ(l2.Size(), 3);
}

TEST(TestLinkedList, CanInsertBeforeInMiddleOfList)
{
	LinkedList<int> l;
	l.PushBack(1);
	l.PushBack(3);
	auto it = l.begin();
	++it;
	l.InsertBefore(it,2);
	auto testit = l.begin();
	ASSERT_EQ(testit.value, 1);
	++testit;
	ASSERT_EQ(testit.value, 2);
	++testit;
	ASSERT_EQ(testit.value, 3);
}

TEST(TestLinkedList, CanInsertBeforeAtStart)
{
	LinkedList<int> l;
	l.PushBack(2);
	l.PushBack(3);
	l.InsertBefore(l.begin(),1);
	auto testit = l.begin();
	ASSERT_EQ(testit.value, 1);
	++testit;
	ASSERT_EQ(testit.value, 2);
	++testit;
	ASSERT_EQ(testit.value, 3);
}

TEST(TestLinkedList, CanInsertBeforeAtStartOfEmpty)
{
	LinkedList<int> l;
	l.InsertBefore(l.begin(),1);
	ASSERT_EQ(l.begin().value, 1);
	
}

TEST(TestLinkedList, CanAssign)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	LinkedList<int> l2;
	l2 = l;
	ASSERT_EQ(l2.Size(), 3);
}

TEST(TestLinkedList, CanDelete)
{
	LinkedList<int> l;
	l.PushBack(0);
	ASSERT_NO_THROW(l.Delete(l.begin()));
	ASSERT_EQ(l.Size(),0);
}

TEST(TestLinkedList, CanFindFirst)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);

	auto it = l.FindFirst(l.begin(), 2);
	ASSERT_NE(it, l.end());
	ASSERT_EQ(it.value,2);
}

TEST(TestLinkedList, CanFindFirstStartingPartWayThrough)
{
	LinkedList<int> l;
	l.PushBack(2);
	l.PushBack(1);
	l.PushBack(2);

	auto start = l.begin();
	++start;
	auto it = l.FindFirst(start,2);
	ASSERT_NE(it, l.end());
	ASSERT_EQ(*it,2);
}

TEST(TestLinkedList, CanFindIfStartingAtFindElement)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);

	auto it = l.FindFirst(l.begin(),0);
	ASSERT_NE(it, l.end());
	ASSERT_EQ(it.value,0);
}

TEST(TestLinkedList, FailureToFindReturnsEnd)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);

	auto it = l.FindFirst(l.begin(), 3);
	ASSERT_EQ(it, l.end());
	
}

TEST(TestLinkedList, DeleteBeforeRetainsIntegrity)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	ASSERT_NO_THROW(l.Delete(l.begin()));
	ASSERT_EQ(l.Size(),1);
	ASSERT_EQ(l.begin().value, 1);
}

TEST(TestLinkedList, DeleteAfterRetainsIntegrity)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	auto it = l.begin();
	++it;
	ASSERT_NO_THROW(l.Delete(it));
	ASSERT_EQ(l.Size(),1);
	ASSERT_EQ(l.begin().value, 0);
}

LinkedList<int> GetListTest()
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	return l;
}

TEST(TestLinkedList, CanMove)
{
	
	LinkedList<int> l2(GetListTest());
	ASSERT_EQ(l2.Size(), 3);
}

TEST(TestLinkedList, CanMoveAssign)
{
	LinkedList<int> l;
	l.PushBack(0);
	l.PushBack(1);
	l.PushBack(2);
	LinkedList<int> l2;
	l2 = GetListTest();
	ASSERT_EQ(l2.Size(), 3);
}
