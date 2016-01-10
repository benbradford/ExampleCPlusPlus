#pragma once

#include <functional>
#include <vector>
#include <sstream>

template <typename KEY, typename VALUE>
class HashMap
{
private:
	struct EntryNode
	{
		KEY key;
		VALUE value;
		std::unique_ptr<EntryNode> next;
	};
public:
	typedef unsigned int DataEntryType;
	typedef unsigned long HashType;
	typedef unsigned int size_type;
	using HashFunction = std::function<HashType(const KEY&)>;
	
	HashMap(const HashFunction& hashFunction, size_type numBuckets = 23);

	struct Iterator
	{
		KEY& first() { return *key; }
		bool operator==(const Iterator& other) const
		{
			return (me == nullptr && other.me == nullptr) 
				|| ( me && other.me && key == other.key && value == other.value);
		}

		bool operator!=(const Iterator& other) const
		{
			return !(*this==other);
		}

		VALUE& operator*() { return *value;}
	
		Iterator operator++()
		{
			
			if (me->next.get()!= nullptr)
			{
				return CreateNext(Iterator{&me->next->key, &me->next->value, me->next.get(), bucketIndex, hashmap});
			}

			for (unsigned int i = 1+bucketIndex; i < hashmap->mNumBuckets; ++i)
			{
				 EntryNode* candidate = hashmap->mDataEntries[i].get();
				if (candidate)
				{
					return CreateNext(Iterator{&candidate->key, &candidate->value, candidate, i, hashmap});
				}
			}
			return CreateNext( hashmap->end());
		
		}
		private:
		KEY* key;
		VALUE* value;
		
		const EntryNode* me;
		unsigned int bucketIndex;
		const HashMap* hashmap;
		friend class HashMap;
		
		Iterator(KEY* k, VALUE* v, const EntryNode* m, unsigned int i, const HashMap* hm)
		: key(k)
		, value(v)
		, me(m)
		, bucketIndex(i)
		, hashmap(hm)		
		{}

		static void swap(Iterator& lhs, Iterator& rhs)
		{
			std::swap(lhs.key,rhs.key);
			std::swap(lhs.value,rhs.value);
			std::swap(lhs.me,rhs.me);
			std::swap(lhs.bucketIndex,rhs.bucketIndex);
			std::swap(lhs.hashmap,rhs.hashmap);
		}

		Iterator CreateNext(Iterator next)
		{
			swap(next, *this);
			return *this;
		}
	};

	VALUE& operator[](const KEY& key);
	Iterator 	find(const KEY& key) ;
	Iterator   	begin();
	Iterator 	end() const{ return {nullptr, nullptr, nullptr,0,nullptr};}
	unsigned int Size() const { return mSize;}
	void Log(std::stringstream& stream) const;
private:

	using DataEntries = std::unique_ptr<std::unique_ptr<EntryNode>[]>;
	
	const HashFunction	mHashFunction;
	const size_type		mNumBuckets;
	DataEntries			mDataEntries;
	int 				mSize;
	
	unsigned int GetHashValue(const KEY& key) const { return mHashFunction(key) % mNumBuckets; }

	Iterator CreateIterator(EntryNode& node, unsigned int index)
	{
		return Iterator{&node.key, &node.value, &node, index, this};
	}
};

template<typename KEY, typename VALUE>
inline HashMap<KEY, VALUE>::HashMap(const HashFunction & hashFunction, size_type numBuckets)
	: mHashFunction(hashFunction)
	, mNumBuckets(numBuckets)
	, mDataEntries(new std::unique_ptr<EntryNode>[numBuckets])
	, mSize(0)
{
}

template<typename KEY, typename VALUE>
inline VALUE& HashMap<KEY, VALUE>::operator[](const KEY & key)
{
	const auto hashIndex = GetHashValue(key);
	const auto dataIndex = hashIndex;
	auto* node = &mDataEntries[dataIndex];
	if (node->get() == nullptr)
	{
		node->reset(new EntryNode{key,VALUE{}});
		++mSize;
	}
	else 
	{
		while((*node)->key != key)
		{
			if ((*node)->next.get() == nullptr)
			{

				(*node)->next.reset(new EntryNode{key,VALUE{}});
				++mSize;
			}

			node = &(*node)->next;
		}
	}

	return (*node)->value;
}

template<typename KEY, typename VALUE>
inline typename HashMap<KEY,VALUE>::Iterator HashMap<KEY, VALUE>::find(const KEY & key)
{
	const auto hashIndex = GetHashValue(key);
	const auto& dataIndex = hashIndex;
	auto* node = &mDataEntries[dataIndex];
	if (node->get() == nullptr)
	{
		return end();
	}
	while((*node)->key != key)
	{
		node = &(*node)->next;
	}
	return CreateIterator(*node->get(), hashIndex);
}

template<typename KEY, typename VALUE>
inline typename HashMap<KEY,VALUE>::Iterator HashMap<KEY, VALUE>::begin()
{
	for (int i=0; i < mNumBuckets; ++i)
	{
		if (mDataEntries[i].get() != nullptr)
		{
			return CreateIterator(*mDataEntries[i], i);
		}
	}
	return end();
}

template<typename KEY, typename VALUE>
inline void HashMap<KEY, VALUE>::Log(std::stringstream& stream) const
	{
		stream << "===LOG=== " <<  "\n";
		for (int i=0; i < mNumBuckets; ++i)
		{
			stream << "Bucket " << i << "\n";
			auto* entry = &mDataEntries[i];
			while (entry->get())
			{
				stream << "Key " << entry->get()->key << " Value " << entry->get()->value << "\n";
				entry = &entry->get()->next;
			}
			stream << "\n";
			
		}
		stream << "====END===\n";
	}

