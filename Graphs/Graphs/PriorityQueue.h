#pragma once
#include <vector>
#include <map>
#include <set>
#include "Node.h"


/*
Time complexity for searching elements in std::map is O(log n).
Even in worst case it will be O(log n) because elements are 
stored internally as Balanced Binary Search tree (BST).
*/

using namespace std;

template <class T>
class PriorityQueue
{
private:
	vector<Node<T>> heap = vector<Node<T>>();
	map<int, set<int>> indexTracker = map<int, set<int>>();

	int heapsize = 0;
	Node<T> dummy = Node<T>(-1, T (-1));

	int parent(int k) { return (k - 1) / 2; }
	int left(int k) { return 2 * k + 1; }
	int right(int k) { return 2 * k + 2; }

	void min_heapify(int k);
	set<int>& getIndexesOf(const int x);
	void replaceIdx(int x, int oldIdx, int newIdx);
	void removeIdx(int x, int idx);
public:
	PriorityQueue();
	~PriorityQueue();
	
	void insert(int x, T p);	//insert
	Node<T>& top();				//maximum
	Node<T> pop();				//extract-max
	void priority(int x, T p);	
	void heapDecreaseKey(int i, T p);

	void print();
	bool empty();
};

template <class T>
void PriorityQueue<T>::replaceIdx(int x, int oldIdx, int newIdx)
{
	set<int>& ids = getIndexesOf(x);	//log(n)
	ids.erase(oldIdx);					//log(n)
	ids.insert(newIdx);					//log(n)
}

template <class T>
void PriorityQueue<T>::min_heapify(int i)
{
	int l = left(i);
	int r = right(i);
	int smallest;
	if (l <= heapsize && heap[l].getPriority() < heap[i].getPriority())
		smallest = l;
	else
		smallest = i;
	if (r <= heapsize && heap[r].getPriority() < heap[smallest].getPriority())
		smallest = r;
	if (smallest != i)
	{
		replaceIdx(heap[i].getKey(), i, smallest);
		replaceIdx(heap[smallest].getKey(), smallest, i);
		swap(heap[i], heap[smallest]);
		min_heapify(smallest);
	}
}

template <class T>
void PriorityQueue<T>::removeIdx(int x, int idx)
{
	getIndexesOf(x).erase(idx);
}

template <class T>
set<int>& PriorityQueue<T>::getIndexesOf(const int x)
{
	return indexTracker[x]; //log(n)
}

template <class T>
PriorityQueue<T>::PriorityQueue()
{

}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{

}

template <class T>
Node<T>& PriorityQueue<T>::top()
{
	if (heap.empty())
		cout << endl;
	else
	{
		((Node<T>) heap[0]).show();
		return heap[0];
	}
}

template <class T>
Node<T> PriorityQueue<T>::pop()
{
	
	if (heapsize < 1)
	{
		return dummy;
	}
	else
	{
		Node<T> max = heap[0];					//max priority has index 0.
		removeIdx(max.getKey(), 0);
		heapsize--;
		heap[0] = heap[heapsize];
		int key = heap[0].getKey();
		removeIdx(key, heapsize);
		min_heapify(0);
		heap.pop_back();
		return max;
	}
}

template <class T>
void PriorityQueue<T>::heapDecreaseKey(int i, T p)
{
	if (p > heap[i].getPriority())
		cout << "new key is bigger than current\n";
	else
	{
		if (indexTracker.count(heap[i].getKey()) == 0)
		{
			set<int> v = set<int>();
			v.insert(i);
			indexTracker.insert({ heap[i].getKey(), v });
		}
		else
		{
			indexTracker[heap[i].getKey()].insert(i);
		}
		heap[i].setPriority(p);
		while (i >= 0 && heap[parent(i)].getPriority() > heap[i].getPriority())
		{

			replaceIdx(heap[i].getKey(), i, parent(i));			
			replaceIdx(heap[parent(i)].getKey(), parent(i), i);	
			swap(heap[i], heap[parent(i)]);
			
			i = parent(i);
		}
	}
}

template <class T>
void PriorityQueue<T>::priority(int x, T p)
{
	set<int> idxs = getIndexesOf(x);
	for (auto i : idxs)
		heapDecreaseKey(i, p);
}

template <class T>
void PriorityQueue<T>::insert(int x, T p)
{
	heapsize++;
	heap.push_back(Node<T>(INT_MAX, x));
	heapDecreaseKey(heapsize-1, p);
}

template <class T>
bool PriorityQueue<T>::empty() 
{
	return heap.empty();
}

template <class T>
void PriorityQueue<T>::print() 
{
	std::cout << "\n";
	for (auto i : heap)
		i.show();
}













