#include "pch.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>

std::map<char, std::vector<int>>
FA::compute_transition_function(std::string pattern, std::set<char> alphabet);
bool FA::isSuffix(std::string suffix, std::string pattern);
void FA::finite_automaton_matcher(std::string text, std::map<char, std::vector<int>> traFunc, int patLen);

int main()
{
	char sigma[] = { 'a', 'b', 'c' };
	std::set<char> alphabet (sigma, sigma+3);
	std::string pattern = "ababaca";
	std::string text = "ababacababacasdababaca";
	auto result = FA::compute_transition_function(pattern, alphabet);
	FA::finite_automaton_matcher(text, result, pattern.length());
}

namespace FA {
	void finite_automaton_matcher(std::string text, std::map<char, std::vector<int>> traFunc, int patLen)
	{
		int n = text.length();
		int q = 0;
		for (int i = 1; i < n; i++)
		{
			if (traFunc.count(text[i]) != 0)
			{
				q = traFunc[text[i]][q];
				if (q == patLen)
					std::cout << "Pattern occurs with shift " << i - patLen << std::endl;
			}
		}
	}

	std::map<char, std::vector<int>>
		compute_transition_function(std::string pattern, std::set<char> alphabet)
	{
		std::map<char, std::vector<int>> result;
		for (unsigned int q = 0; q < pattern.length() + 1; q++)
		{
			for (char c : alphabet)
			{
				if (result.count(c) == 0)
					result[c] = std::vector<int>(pattern.length() + 1);
				int k = std::min(pattern.length() + 1, q + 2);
				do {
					k--;
				} while (isSuffix(pattern.substr(0, k), pattern.substr(0, q) + c));
				result[c][q] = k;
			}
		}
		return result;
	}

	bool isSuffix(std::string suffix, std::string pattern)
	{
		if (suffix.length() == 0)
			return false;
		int startAt = pattern.length() - suffix.length();
		std::string patternSuffix = pattern.substr(startAt, suffix.length());
		return suffix.compare(patternSuffix) != 0;
	}
}

