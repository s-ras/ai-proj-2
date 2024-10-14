#include <chrono>
#include "./include/datastructures.h"

const int START = 4;
const int MAX_DEPTH = 1000;

void gather_input(int&);

OP* IDS(int, int);

int main() {
	int goal;

	gather_input(goal);

	OP* solution = NULL;

	auto start = std::chrono::high_resolution_clock::now();

	solution = IDS(START, goal);

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

	if (solution != NULL) {
		solution->print_path();
	}

	return 0;
}

void gather_input(int& goal) {
	std::cout << "Which number are you trying to reach? ";
	std::cin >> goal;
}

OP* IDS(int start, int goal) {
	for (int depth = 0; depth <= MAX_DEPTH; depth++) {
		std::unordered_map<double, OP*> explored;
		OP* root = new OP(start, "root", NULL);
		OP* solution = root->DFS(goal, depth, explored);
		if (solution) {
			return solution;
		}
		delete root;
	}
	return NULL;
}