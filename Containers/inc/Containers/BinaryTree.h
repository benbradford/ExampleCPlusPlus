#pragma once
#include <memory>
#include <cassert>
#include <list>
template <typename T>
class BinaryTree
{
private:
	struct Node
	{
		T value;
		Node* parent = nullptr;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		
	};

public:
	class Iterator
	{
	public:
		bool operator==(const Iterator& other) const { return node == other.node; }
		bool operator!=(const Iterator& other) const { return !(*this == other); }

		Iterator operator++()
		{
			
			if (node == finalNode)
			{
				node = nullptr;
				return *this;
			}
			else
			{
				if (node->left.get() && (!last || last != node->left.get()))
				{
					node = SearchDown(node->left.get());
					last = node;
					
				}
				else if (node->right.get() && (!last || last != node->right.get()))
				{
					node = SearchDown(node->right.get());
					last = node;
				}
				else if (node->parent)
				{					
					if (node->parent->left.get() == node)
					{
						last = node;
						node = node->parent;
						--depth;
					}
					else 
					{
						node = SearchUp(node);
					}	
				}
				else
				{
					// only 1 node in the tree
					assert(last == nullptr);
					node = nullptr; // end
				}
			
				if (node)
					value = &node->value;
			}
			return *this;
		}

		T& operator*() { return *value;}

		Node* SearchUp(Node* node)
		{
			--depth;
			last = node;
			if (node == nullptr || node->parent == nullptr)
				return nullptr;
			if (node->parent->right.get() == node)
			{
				return SearchUp(node->parent);
			}
			return node->parent;
			
		}

		Node* SearchDown(Node* node)
		{
			++depth;
			//assert(node->left.get() || node->right.get());
			if (node->left.get() && node->left.get() != last)
			{				
				last = node;
				
				return SearchDown(node->left.get());
			}
			else 
			{
				if (last == node)
				{
					return SearchDown(node->right.get());
				}
				
			}
			return node;
		}
	private:
		T* value;
		Node* node;
		Node* last;
		Node* finalNode;
	public:
		unsigned int depth;
	private:
		friend class BinaryTree;
		Iterator(T* v, Node* n, Node* finalN)
		: value(v)
		, node(n)
		, last(nullptr)
		, finalNode(finalN)
		, depth(0)
		{
			if (node)
			{	
				depth = 1;
				Node* depthFinder = node;
				while (depthFinder->parent)
				{
					++depth;
					depthFinder = depthFinder->parent;
				}
			}
		}
	};
	BinaryTree()
	: mSize(0)
	{}

	BinaryTree(const BinaryTree&) = delete;
	BinaryTree(BinaryTree&&) = delete;
	BinaryTree& operator=(const BinaryTree&)=delete;
	BinaryTree& operator=(BinaryTree&&)=delete;

	void Add(const T& value)
	{
		if (mRoot.get() == nullptr)
		{
			mRoot.reset(new Node{value, nullptr});
		}
		else 
		{
			auto node = &mRoot;
			while (true)
			{
				if (value < node->get()->value)
				{
					if (node->get()->left.get() == nullptr)
					{
						node->get()->left.reset(new Node{value, node->get()});
						break;
					}
					else 
					{
						node = &node->get()->left;
					}
				}
				else 
				{
					if (node->get()->right.get() == nullptr)
					{
						node->get()->right.reset(new Node{value, node->get()});
						break;
					}
					else 
					{
						node = &node->get()->right;
					}
				}
			}
		}
		++mSize;
	}
	//void Add(T&& value);

	Iterator begin() const 
	{ 
		if (mRoot.get())
		{

			Node* node = mRoot.get();
			while (node->left.get())
				node = node->left.get();
		 	return Iterator{&node->value, node, GetLast()};
		} 
		return end();
	}
	Iterator end() const { return Iterator{nullptr, nullptr, nullptr};}

	unsigned int Size() const { return mSize; }

	Iterator FindFirst(const Iterator& from, const T& value);

	std::list<Iterator> GetAllAtDepth(unsigned int depth) const 
	{
		std::list<Iterator> list;
		auto e = end();
		for (Iterator it = begin(); it != e; ++ it)
		{
			if (it.depth == depth)
				list.push_back(it);
		}
		return list;

	}
private:
	std::unique_ptr<Node> mRoot;
	unsigned int mSize;
	Node* GetLast() const
	{
		if (mRoot.get())
		{

			Node* node = mRoot.get();
			while (node->right.get())
				node = node->right.get();

			return node;
		} 
		return nullptr;
	}
};