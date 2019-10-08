#include "pch.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <array>
#include <string>

namespace FA
{
  std::map<char, std::vector<int>>
  compute_transition_function(std::string pattern, std::set<char> alphabet);
  bool isSuffix(std::string suffix, std::string pattern);
  std::set<char> charsIn(std::string pattern);
  void finite_automaton_matcher(std::string pattern, std::string text);
}

namespace KMP
{
  int* compute_prefix_function(const std::string text);
  void kmp_matcher(const std::string p, const std::string t);
}

int main()
{
  std::string pattern, text, choice;
  std::cout << "Pattern: ";
  getline(std::cin, pattern);
  std::cout << "Text: ";
  getline(std::cin, text);
  std::cout << "F for string matching with finite automaton" << std::endl;
  std::cout << "K for string matching with knuth-morris-pratt algorithm" << std::endl;
  getline(std::cin, choice);
  if (choice.compare("K") == 0)
    KMP::kmp_matcher(pattern, text);
  else if (choice.compare("F") == 0)
    FA::finite_automaton_matcher(pattern, text);
  else
    std::cout << "Incorrect parameter, bye" << std::endl;
  return 0;
}

namespace FA {
	void finite_automaton_matcher(std::string pattern, std::string text)
	{
    int patLen = pattern.length();
    std::set<char> alphabet = charsIn(pattern);

    auto traFunc = compute_transition_function(pattern, alphabet);

		int n = text.length();
		int q = 0;
		for (int i = 0; i < n; i++)
		{
			if (traFunc.count(text[i]) != 0)
			{
				q = traFunc[text[i]][q];
				if (q == patLen)
					std::cout << "Pattern occurs with shift " << i - patLen + 1 << std::endl;
			} 
      else
      {
        q = 0;
      }
		}
	}

  std::set<char> charsIn(std::string pattern)
  {
    std::set<char> result = std::set<char>();
    for (char c : pattern)
      result.insert(c);
    return result;
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

namespace KMP
{
  void kmp_matcher(const std::string p, const std::string t)
  {
    int n = t.length();
    int m = p.length() - 1;
    int * pi = compute_prefix_function(p);
    int q = -1;
    for (int i = 0; i < n; i++)
    {
      while (q > -1 && p[q + 1] != t[i])
        q = pi[q];
      if (p[q + 1] == t[i])
        q++;
      if (q == m)
      {
        std::cout << "Pattern occurs with shift " << i - m;
        q = pi[q];
      }
    }
  }

  int* compute_prefix_function(const std::string text)
  {
    int m = text.length();
    int * result = new int[m];
    result[0] = -1;
    int k = -1;
    for (int q = 1; q < m; q++)
    {
      while (k > -1 && text[k + 1] != text[q])
        k = result[k];
      if (text[k + 1] == text[q])
        k++;
      result[q] = k;
    }
    return result;
  }
}