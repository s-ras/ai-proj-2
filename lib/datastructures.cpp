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

void OP::expand() {
	double d_sqrt = sqrt(this->data);
	double d_floor = floor(this->data);
	double d_times_two = this->data * 2;

	this->left = new OP(d_sqrt, "sqrt", this);

	this->middle = new OP(d_floor, "floor", this);

	this->right = new OP(d_times_two, "times_two", this);
}

OP* OP::DFS(int goal, int depth) {
	if (this->data == goal) {
		return this;
	}
	if (this->d >= depth) {
		return NULL;
	}
	this->expand();

	OP* children[] = {this->right, this->middle, this->left};

	for (int i = 0; i < 3; i++) {
		if (children[i] == NULL) {
			continue;
		}
		OP* solution = children[i]->DFS(goal, depth);
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

void OP::print() {
	if (this->type == "root") {
		std::cout << "start at " << this->data << std::endl;
	} else if (this->type == "sqrt") {
		std::cout << "sqrt(" << this->parent->data << ") = " << this->data
				  << std::endl;
	} else if (this->type == "floor") {
		std::cout << "floor(" << this->parent->data << ") = " << this->data
				  << std::endl;
	} else if (this->type == "times_two") {
		std::cout << this->parent->data << " * 2 = " << this->data << std::endl;
	}
}

void OP::print_path() {
	if (this->parent) {
		this->parent->print_path();
	}
	this->print();
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
