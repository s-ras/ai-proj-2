#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <math.h>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

class BST;
class OP;

class OP {
  public:
	double data;
	std::string type;

	OP* parent = NULL;

	OP* left = NULL;
	OP* middle = NULL;
	OP* right = NULL;

	int d = 0;

	OP(double, std::string, OP*);

	OP* DFS(int, int, std::unordered_map<double, OP*>&);

	void expand(std::unordered_map<double, OP*>&);

	void print_path();

	void delete_sub_tree();
};

#endif