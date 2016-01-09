#pragma once

#include <memory>

template <typename T>
class LinkedList
{
private:
	struct Node
	{
		T value;
		std::unique_ptr<Node> next;
	};
public:

	
	struct Iterator
	{
		T value;

		bool operator==(const Iterator& other) const { return index == other.index;}
		bool operator!=(const Iterator& other) const { return !(*this == other);}
		Iterator operator++()
		{
			++index;
				
			if (node && node->next.get())
			{
				node = node->next.get();
				value = node->value;
			}
			return *this;
		}
		T& operator*() { return value;}

	private:
		Node* node;
		unsigned int index;

		Iterator(const T& v, Node* n, unsigned int i)
		: value(v)
		, node(n)
		, index(i)
		{}

		friend class LinkedList;
	};
	LinkedList() :mSize(0){}
	LinkedList(const LinkedList& other)
	: mSize(other.mSize)
	{
		DeepCopy(other);
	}

	LinkedList& operator=(const LinkedList& other)
	{
		mSize = other.mSize;
		DeepCopy(other);
		return *this;
	}

	LinkedList(LinkedList&&) = default;
	LinkedList& operator=(LinkedList&&) =default;

	Iterator begin() const { if (mSize == 0) return end(); return Iterator{mStart->value, mStart.get(), 0};}
	Iterator end() const { return Iterator{T{}, nullptr, mSize};}
	
	void PushBack(const T& value)
	{
		if (mStart.get() == nullptr)
		{
			mStart.reset(new Node{value});
		}
		else 
		{
			Node* curr = mStart.get();
			Node* next = curr;
			while (next)
			{
				next = curr->next.get();
				if (next)
					curr = next;
			}
			curr->next.reset(new Node{value});
		}
		++mSize;
	}

	void InsertAfter(const Iterator& position, const T& value)
	{
		std::unique_ptr<Node> newNode(new Node{value, std::move(position.node->next)});
		position.node->next = std::move(newNode);
		++mSize;
	}

	void Delete(const Iterator& position)
	{
		if (position.index == 0)
		{
			mStart = std::move(position.node->next);
		}
		else 
		{
			std::unique_ptr<Node>* before = &mStart;
			for (auto i = 0u; i < position.index-1; ++i)
			{
				before = &(*before)->next;
			}
			(*before)->next = std::move(position.node->next);
		}
		--mSize;
	}

	Iterator FindFirst(const Iterator& searchFrom, const T& value) const
	{
		Node* search = searchFrom.node;
		unsigned int count = 0;
		while(search)
		{
			if (search->value == value)
			{
				return Iterator{value, search, searchFrom.index + count};
			}
			++count;
			search = search->next.get();
		}
		return end();
	}

	unsigned int Size() const { return mSize; }
	static void swap(LinkedList& lhs, LinkedList& rhs)
	{
		std::swap(lhs.mSize, rhs.mSize);
		std::swap(lhs.mStart, rhs.mStart);
	}
private:
	std::unique_ptr<Node> mStart;
	unsigned int mSize;

	void DeepCopy(const LinkedList& other)
	{
		if (other.mStart.get())
		{
			mStart.reset(new Node{other.mStart->value});
			std::unique_ptr<Node>* next = &other.mStart->next;
			std::unique_ptr<Node>* curr = &mStart;
			while (next->get())
			{
				printf("Copying %i\n", (*next)->value);
				(*curr)->next.reset(new Node{(*next)->value});
				
				curr = &(*curr)->next;
				next = &(*next)->next;

			}
		}
	}
};