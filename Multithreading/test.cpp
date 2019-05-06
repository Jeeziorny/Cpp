#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <stack>
#include <fstream>
#include <atomic>
#include <algorithm>
#include <string>
#include <chrono>


void read();
void process();
void read_and_process();

std::mutex locker;
std::atomic<bool> eof(false);
std::stack<std::string> words;

int main(void) {
	auto start = std::chrono::system_clock::now();
	std::thread fst(read);
	std::thread scn(process);
	fst.join();
	scn.join();
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast
		<std::chrono::milliseconds>(end - start);
	std::cout << "Time elapsed (two threads): " << elapsed.count() << std::endl;
	start = std::chrono::system_clock::now();
	read_and_process();
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast
		<std::chrono::milliseconds>(end - start);
		std::cout << "Time elapsed (single thread): " << elapsed.count() << std::endl;
	return 0;
}

void read_and_process() {
	std::ifstream reddo;
	std::string temp;
	long long int sum = 0;
	reddo.open("sample.txt");
	while (!reddo.eof()) {
		reddo >> temp;
		sum += std::count(temp.begin(), temp.end(), 'a');
	}
	std::cout << "There were " << sum << " occurrences of a " << std::endl;
}

void read() {
	std::ifstream reddo;
	std::string temp;
	reddo.open("sample.txt");
	while (!reddo.eof()) {
		reddo >> temp;
		{
			std::lock_guard<std::mutex> guard(locker);
			words.push(temp);
		}
	}
	temp = "---";
	std::lock_guard<std::mutex> guard(locker);
	words.push(temp);
}

void process() {
	std::string s = "";
	std::string t = "";
	bool end = false;
	long long int sum = 0;
	while (!end) {
		{
			std::lock_guard<std::mutex> guard(locker);
			if (!words.empty()) {
				s = words.top();
				words.pop();
			}
			if (s == "---") {
				while (true) {
					if (words.empty()) {
						s = "";
						end = true;
						break;
					}
					t = words.top();
					words.pop();
					sum += std::count(t.begin(), t.end(), 'a');
				}
			}
		}
		sum += std::count(s.begin(), s.end(), 'a');
		s = "";
	}
	std::cout << "There were " << sum << " occurrences of a " << std::endl;
}








