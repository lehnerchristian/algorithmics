#include <iostream>
#include <stdio.h>
#include <chrono>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;


std::chrono::high_resolution_clock::time_point start;
std::chrono::duration<double> time_taken;

const unsigned MAX_TIME = 300; // 5 min
const unsigned NUMBERS_COUNT = 4;
const unsigned RUNS_COUNT = 5;

mpz_class fibonacci(unsigned n) {
	time_taken = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start);
	if(time_taken.count() < MAX_TIME) {
		if(n <= 2) return 1;
		else return fibonacci(n - 1) + fibonacci(n - 2);
	}
	else {
		throw "Max time exceeded max time -> Infinity\n";
	}
}

void print_success(unsigned numbers[], double average_runtimes[]) {
	for (int i = 0; i < NUMBERS_COUNT; ++i) {
		cout << "Average runtime " << numbers[i] << ":\t" << average_runtimes[i] << endl;
	}
}

void print_failure(unsigned numbers[], double average_runtimes[]) {
	for (int i = 0; i < NUMBERS_COUNT; ++i) {
		if(average_runtimes[i] != 0) {
			cout << "Runtime " << numbers[i] << ":\t" << average_runtimes[i] << endl;	
		}
		else {
			cout << "Runtime " << numbers[i] << ":\tINF" << endl;	
		}
	}
}

int main() {
	cout << "\nMAX RUNTIME set to " << MAX_TIME << " seconds\n" << endl;
	unsigned numbers[NUMBERS_COUNT] = { 100, 1000, 10000, 1000000 };
	double average_runtimes[NUMBERS_COUNT] = { 0 };

	for(unsigned i = 0; i < NUMBERS_COUNT; i++) {
		double runtime = 0;
		for(unsigned j = 0; j < RUNS_COUNT; j++) {
			try {
				start = std::chrono::steady_clock::now();
				fibonacci(numbers[i]);
				time_taken = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - start);
				cout << "Fib(" << numbers[i] << "): done..." << endl;	
				runtime += time_taken.count();
			}
			catch(const char* e) {
				cout << e << endl;
				print_failure(numbers, average_runtimes);
				return 0;
			}
		}
		average_runtimes[i] = runtime/RUNS_COUNT;
	}
	print_success(numbers, average_runtimes);
	return 0;
}