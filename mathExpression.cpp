#include "mathExpression.h"

mathExpression::mathExpression()
{
}

mathExpression::mathExpression(std::string s)
{
	this->Parse(s);
}

void mathExpression::Parse(std::string s)
{
	std::string temp;
	int brackets = -1;
	// f*(b+6/5+a*8)
	for (int i = 0; i < s.length(); i++)
	{
		char symbol = s.at(i);
		if (symbol == '(')
		{
			if (symbol == -1) symbol++;
			brackets++;
		}
		else if (symbol == ')')
		{
			brackets--;
		}

		if (i != 0 && brackets == 0)
		{
		}
	}
}
