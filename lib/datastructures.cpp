#include "../include/datastructures.h"

OP::OP(double data, std::string type, OP* parent) {
	this->data = data;
	this->type = type;

	this->parent = parent;

	this->left = NULL;
	this->middle = NULL;
	this->right = NULL;

	if (this->type == "root") {
		this->d = 0;
	} else {
		this->d = this->parent->d + 1;
	}
}

void OP::expand(std::unordered_map<double, OP*>& explored) {
	double d_sqrt = sqrt(this->data);
	double d_floor = floor(this->data);
	double d_times_two = this->data * 2;

	if (explored.find(d_sqrt) == explored.end()) {
		this->left = new OP(d_sqrt, "sqrt", this);
	}

	if (explored.find(d_floor) == explored.end()) {
		this->middle = new OP(d_floor, "floor", this);
	}

	if (explored.find(d_times_two) == explored.end()) {
		this->right = new OP(d_times_two, "times_two", this);
	}
}

OP* OP::DFS(int goal, int depth, std::unordered_map<double, OP*>& explored) {
	if (this->data == goal) {
		return this;
	}
	explored[this->data] = this;
	if (this->d >= depth) {
		return NULL;
	}
	this->expand(explored);

	OP* children[] = {this->right, this->middle, this->left};

	for (int i = 0; i < 3; i++) {
		if (children[i] == NULL) {
			continue;
		}
		OP* solution = children[i]->DFS(goal, depth, explored);
		if (solution) {
			return solution;
		} else {
			children[i]->delete_sub_tree();
			delete children[i];
			if (i == 0) {
				this->right = NULL;
			} else if (i == 1) {
				this->middle = NULL;
			} else if (i == 2) {
				this->left = NULL;
			}
		}
	}

	return NULL;
}

void OP::print_path() {
	std::stack<OP*> s;

	OP* current = this;

	while (current != NULL) {
		s.push(current);
		current = current->parent;
	}

	while (s.size() > 0) {
		OP* op = s.top();
		s.pop();
		if (op->type == "root") {
			std::cout << "start at " << op->data << std::endl;
		} else if (op->type == "sqrt") {
			std::cout << "sqrt(" << op->parent->data << ") = " << op->data
					  << std::endl;
		} else if (op->type == "floor") {
			std::cout << "floor(" << op->parent->data << ") = " << op->data
					  << std::endl;
		} else if (op->type == "times_two") {
			std::cout << op->parent->data << " * 2 = " << op->data << std::endl;
		}
	}
}

void OP::delete_sub_tree() {
	if (this->left) {
		this->left->delete_sub_tree();
		delete this->left;
		this->left = NULL;
	}
	if (this->middle) {
		this->middle->delete_sub_tree();
		delete this->middle;
		this->middle = NULL;
	}
	if (this->right) {
		this->right->delete_sub_tree();
		delete this->right;
		this->right = NULL;
	}
}
