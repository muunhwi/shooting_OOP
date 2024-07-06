#pragma once
#include <initializer_list>
#include <utility>

template <typename T>
class MyLinkedList
{
public:
	struct Node
	{
		T  _data;
		Node* _Prev;
		Node* _Next;
	};
	class iterator
	{
	private:
		Node* _node;
	public:
		iterator(Node* node = nullptr)
			: _node{ node }
		{
		}

		iterator operator ++(int)
		{
			iterator ret = iterator(_node);
			_node = _node->_Next;
			return ret;
		}

		iterator& operator++()
		{
			_node = _node->_Next;
			return *this;
		}

		iterator operator --(int)
		{
			iterator ret = iterator(_node);
			_node = _node->_Prev;
			return ret;
		}

		iterator& operator--()
		{
			_node = _node->_Prev;
			return *this;
		}

		T& operator *()
		{
			return _node->_data;
		}
		bool operator ==(const iterator& other)
		{
			if (this == &other)
				return true;

			if (_node->_data == other._node->_data &&
				_node->_Next == other._node->_Next &&
				_node->_Prev == other._node->_Prev)
				return true;

			return false;

		}
		bool operator !=(const iterator& other)
		{
			return !(operator==(other));
		}

	};
public:
	MyLinkedList()
	{
		_head._Next = &_tail;
		_tail._Prev = &_head;
	}
	MyLinkedList(std::initializer_list<T> list)
		: MyLinkedList()
	{
		for (auto it{ list.begin() }; it != list.end(); ++it)
			push_back(*it);
	}
	MyLinkedList(iterator begin, iterator end)
		: MyLinkedList()
	{
		for (; begin != end; ++begin)
			push_back(*begin);
	}
	MyLinkedList(const MyLinkedList& list)
		: MyLinkedList()
	{
		Node const* cur = list._head._Next;

		while (cur != &list._tail)
		{
			push_back(cur->_data);
			cur = cur->_Next;
		}
	}
	MyLinkedList(MyLinkedList&& list) noexcept
		: MyLinkedList()
	{
		swap(list);
	}
	MyLinkedList& operator=(const MyLinkedList& rhs)
	{
		clear();

		MyLinkedList temp{ rhs };
		swap(temp);

		return *this;
	}
	MyLinkedList& operator=(MyLinkedList&& rhs) noexcept
	{
		clear();
		swap(rhs);
		return *this;
	}
	~MyLinkedList()
	{
		clear();
	}

	iterator begin()
	{
		iterator it{ _head._Next };

		return it;
	}
	iterator end()
	{
		iterator it{ &_tail };

		return it;
	}
	iterator erase(iterator it)
	{
		if (empty())
			return end();

		Node* curNode = _head._Next;
		T& curData = *it;

		while (curNode->_data != curData)
			curNode = curNode->_Next;

		curNode->_Prev->_Next = curNode->_Next;
		curNode->_Next->_Prev = curNode->_Prev;

		_size--;
		iterator ret(curNode->_Next);
		delete curNode;

		return ret;
	}

	void push_front(const T& data)
	{
		Node* firstNode = &_head;

		Node* newNode = new Node{ data, firstNode, firstNode->_Next };

		firstNode->_Next->_Prev = newNode;
		firstNode->_Next = newNode;

		_size++;
	}


	void push_back(const T& data)
	{
		Node* lastNode = _tail._Prev;
		Node* newNode = new Node{ data, lastNode, lastNode->_Next };

		lastNode->_Next->_Prev = newNode;
		lastNode->_Next = newNode;

		_size++;
	}


	void pop_front()
	{
		if (empty()) return;

		Node* delNode = _head._Next;

		delNode->_Next->_Prev = delNode->_Prev;
		_head._Next = delNode->_Next;

		_size--;
		delete delNode;

	}
	void pop_back()
	{
		if (empty()) return;

		Node* delNode = _tail._Prev;

		delNode->_Prev->_Next = delNode->_Next;
		_tail._Prev = delNode->_Prev;

		_size--;
		delete delNode;
	}
	void remove(const T& data)
	{
		MyLinkedList<T>::iterator iter;
		for (iter = begin(); iter != end(); ++iter)
		{
			if (*iter == data)
				erase(iter);
		}
	}
	void clear() noexcept
	{
		while (!empty())
		{
			pop_front();
		}

	}
	bool empty() const noexcept
	{
		if (_size > 0)
			return false;
		else
			return true;
	}

	size_t size() const { return _size; };
	void swap(MyLinkedList& rhs) noexcept
	{
		std::swap(_size, rhs._size);

		std::swap(_head._Next->_Prev, rhs._head._Next->_Prev);
		std::swap(_head._Next, rhs._head._Next);

		std::swap(_tail._Prev->_Next, rhs._tail._Prev->_Next);
		std::swap(_tail._Prev, rhs._tail._Prev);

	}

private:
	size_t _size = 0;
	Node _head;
	Node _tail;
};

template <typename T>
void swap(MyLinkedList<T>& lhs, MyLinkedList<T>& rhs) noexcept
{
	lhs.swap(rhs);
}