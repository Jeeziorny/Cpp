#include "pch.h"
#include "../Graphs/PriorityQueue.h"
#include "gtest/gtest.h"
#include <vector>
#include <algorithm>		//std::shuffle
#include <random>			//std::default_random_engine 
#include <chrono>			//std::chrono::system_clock


class PTest : public ::testing::Test
{
private:
	const int SIZE = 100;

protected:
	virtual void setUp()
	{
		std::vector<int> temp = std::vector<int>();
		for (int i = 0; i < SIZE; i++) { temp.push_back(i); }
		unsigned seed = std::chrono::system_clock::now()
			.time_since_epoch().count();
		std::shuffle(temp.begin(), temp.end(), std::default_random_engine(seed));
		for (int i = 0; i < SIZE; i++) { pq.insert(i, i); }
	}

	virtual void TearDown()
	{

	}
public:
	PriorityQueue<int> pq = PriorityQueue<int>();
};

TEST_F(PriorityQueueTest, PopTest)
{
	double currentPriority, prevPriority;
	prevPriority = (double)INT_MAX;
	while (!pq.empty())
	{
		currentPriority = pq.pop().getPriority();
		if (currentPriority > prevPriority)
			std::cout << "klops";
		prevPriority = currentPriority;
	}
}