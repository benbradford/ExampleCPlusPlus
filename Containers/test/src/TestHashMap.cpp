#include "test/TestCommon.h"
#include "Containers/HashMap.h"
#include <unordered_map>
#include <iostream>

struct intinthash
{
	static unsigned long hash(int i)
	{
		return i;
	}
};
TEST(TestHashMap, CanAdd)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	map[5] = 10;
	map[6] = 16;
	ASSERT_EQ(map[5] , 10);
}

TEST(TestHashMap, CanAddAndChange)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	map[5] = 10;
	map[5] = 16;
	ASSERT_EQ(map[5] , 16);
}

TEST(TestHashMap, CanHandleDuplicates)
{
	HashMap<int,int> map([](...){return 0;});
	map[0] = 0;
	map[1] = 1;
	ASSERT_EQ(map[0] , 0);
	ASSERT_EQ(map[1] ,1);
}

TEST(TestHashMap, CanGetSize)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	ASSERT_EQ(map.Size() , 0);
	
	map[0] = 0;
	ASSERT_EQ(map.Size() , 1);
	
	map[1] = 1;
	ASSERT_EQ(map.Size() ,2);
}

TEST(TestHashMap, CanGetSizeWithKeyClashes)
{
	HashMap<int,int> map([](...){return 0;});
	ASSERT_EQ(map.Size() , 0);
	
	map[0] = 0;
	ASSERT_EQ(map.Size() , 1);
	
	map[1] = 1;
	ASSERT_EQ(map.Size() ,2);
}

TEST(TestHashMap, ValidFindWillReturnValidIterator)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	map[0] = 0;
	ASSERT_NE(map.find(0), map.end());
}

TEST(TestHashMap, FailureToFindWillReturnEnd)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	ASSERT_EQ(map.find(0), map.end());
}

TEST(TestHashMap, CanFindValidEntry)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	map[0] = 5;
	ASSERT_EQ(map.find(0).value, 5);
}

TEST(TestHashMap, CanManiupluatePointerInValidFind)
{
	HashMap<int,int*> map(std::bind(intinthash::hash,std::placeholders::_1));
	int myInt = 5;
	map[0] = &myInt;
	auto found = map.find(0);
	(*found.value)++;
	ASSERT_EQ(myInt,6);
}

TEST(TestHashMap, BeginWillReturnOnlyEntryInHashmap)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	map[0] = 5;
	ASSERT_EQ(map.begin(), map.find(0));
}

TEST(TestHashMap, BeginWillReturnEndInEmptyHashmap)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1));
	ASSERT_EQ(map.begin(), map.end());
}

TEST(TestHashMap, CanIterate)
{
	HashMap<int,int> map(std::bind(intinthash::hash,std::placeholders::_1), 4);
	std::unordered_map<int,int> um;
	map[1] = 1;
	map[2] = 2;
	map[3] = 3;
	map[4] = 4;
	map[5] = 5;
	std::stringstream s;
	map.Log(s);
	using namespace std;
	cout << s.str().c_str() << endl;
	for (HashMap<int,int>::Iterator it = map.begin(); it != map.end(); ++it)
	{
		um[it.key] = it.value;
	}
	ASSERT_EQ(um.size(), map.Size());
}

