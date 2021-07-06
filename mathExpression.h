#pragma once
#include <string>

struct node
{
	std::string val;
	node* left;
	node* right;

	node(): left(nullptr), right(nullptr) {}
};

class mathExpression
{
public:
	mathExpression();
	mathExpression(std::string s);

	void Parse(std::string s);

private:
	node root;
};

