#pragma once
#include <iostream>

template <class T>
class Node
{
private:
	T priority;
	int key;
public:
	Node(T p, int k);
	~Node();

	void setPriority(T p);
	T getPriority();
	void setKey(int k);
	int getKey();
	void show();
};

template <class T>
Node<T>::Node(T p, int k)
{
	priority = p;
	key = k;
}

template <class T>
Node<T>::~Node()
{
}

template <class T>
void Node<T>::setPriority(T p)
{
	priority = p;
}

template <class T>
T Node<T>::getPriority()
{
	return priority;
}

template <class T>
void Node<T>::setKey(int k)
{
	key = k;
}

template <class T>
int Node<T>::getKey()
{
	return key;
}

template <class T>
void Node<T>::show()
{
	std::cout << "(" << key << ", " << priority << ") ";
}
