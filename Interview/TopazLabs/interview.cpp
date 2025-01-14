/*
1. Write a function that generates a random string of a given length.
2. Write a function that given a string, 
counts the number of occurences of each character.
*/

#include <iostream>
#include <vector>
#include <string>
// to generate seed
#include "time.h"
#include <cstdlib>
// to keep the dictionary
#include <unordered_map>
// for multithreading
#include "pthread.h"
// for std::thread instead of posix threads
#include <thread>
using namespace std;

string generateRandomString (int n) {
	string s = "";
	srand(time(0));
	for (int i = 0; i < n; i++) {
		int tmp = rand() % 256;
		s.push_back(static_cast<char>(tmp));
	}
	return s;
}

unordered_map<char, int> stringToDict (string s) {
	unordered_map<char, int> hashMap;
	for (auto &ch : s) {
		if (hashMap.find(ch) != hashMap.end())
			hashMap[ch]++;
		else
			hashMap[ch] = 1;
	}
	return hashMap;
}

#define max_threads 8
unordered_map<char, int> um;


// also comment out the entry creation lines.
void* stringToDictMultithreadedFail (void* input) {
	string *s = (string *) input;
	// cout << *s << endl;
	for (auto ch : *s) {
		if (um.find(ch) != um.end())
			um[ch]++;
		else
			um[ch] = 1;
	}
	pthread_exit(NULL);
}

void* stringToDictMultithreaded (void* input) {
	string *s = (string *) input;
	// cout << *s << endl;
	for (auto ch : *s) {
		um[ch]++;
	}
	pthread_exit(NULL);
}

void stringToDictMultithreaded2 (string& s, int start, int end) {
	for (int i = start; i <= end; i++)
		um[s[i]]++;
	pthread_exit(NULL);
}

int main () {
	int n = 1000;
	string s = generateRandomString(n);
	cout << s << endl;
	unordered_map<char, int> hashMap = stringToDict(s);
	for (auto &i : hashMap)
		cout << i.first << " " << i.second << endl;

	// chop the strings in max_threads part
	vector<string> chopped_s(max_threads, "");
	int chopped_length = s.length() / max_threads;
	for (int i = 0; i < max_threads; i++) {
		int start = i * chopped_length;
		for (int j = 0; j < chopped_length; j++)
			chopped_s[i].push_back(s[start + j]);
	}

	// create entries for the chars
	for (int i = 0; i < 256; i++)
		um[static_cast<char>(i)] = 0;

	pthread_t thread[max_threads];
	for (int i = 0; i < max_threads; i++)
		pthread_create(&thread[i], NULL, &stringToDictMultithreaded, (void *) &chopped_s[i]);
	for (int i = 0; i < max_threads; i++)
		pthread_join(thread[i], NULL);

	// match the serial result with the parallel one
	for (auto &ch : um)
		if (ch.second != hashMap[ch.first])
			cout << "found" << endl;
	cout << "Done this round" << endl;	

	um.clear();
	for (int i = 0; i < 256; i++)
		um[static_cast<char>(i)] = 0;

	std::thread th1(stringToDictMultithreaded2, std::ref(s), 0, n / 2 - 1);
	std::thread th2(stringToDictMultithreaded2, std::ref(s), n / 2, n - 1);
	th1.join();
	th2.join();

	for (auto &ch : um)
		if (ch.second != hashMap[ch.first])
			cout << "found" << endl;
	return 0;
}

// how do you do this with reduce?