#include <chrono>
#include "./include/datastructures.h"

const int BASE = 4;
const int MAX_DEPTH = 1000;

void gather_input(int&, int&);

OP* IDS(int, int, int);

int main() {
	int goal, alg;

	gather_input(goal, alg);

	OP* solution = NULL;

	auto start = std::chrono::high_resolution_clock::now();

	switch (alg) {
		case 1:
			solution = IDS(BASE, goal, 1);
			break;
		case 2:
			solution = IDS(BASE, goal, (int)floor(log2(goal)));
			break;
		default:
			break;
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

	if (solution != NULL) {
		solution->print_path();
	}

	return 0;
}

void gather_input(int& goal, int& alg) {
	std::cout << "Which number are you trying to reach? ";
	std::cin >> goal;
	std::cout << "Which algorithm do you want to use? " << std::endl;
	std::cout << "1 - IDS starting at 1 initial depth" << std::endl;
	std::cout << "2 - IDS starting at log2 initial depth" << std::endl;
	std::cout << "? ";
	std::cin >> alg;
}

OP* IDS(int base, int goal, int init_depth) {
	for (int depth = init_depth; depth <= MAX_DEPTH; depth++) {
		OP* root = new OP(base, "root", NULL);
		OP* solution = root->DFS(goal, depth);
		if (solution) {
			return solution;
		}
		delete root;
	}
	return NULL;
}