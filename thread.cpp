#include "main.h"

void test_thread() {
	static std::map<THREAD_ID, std::string> threads;

	THREAD_ID id = 0;
	threads.erase(id);

	threads.insert(std::map<THREAD_ID, std::string>::value_type(1, "test"));
	threads.insert(std::map<THREAD_ID, std::string>::value_type(1, "test"));
}