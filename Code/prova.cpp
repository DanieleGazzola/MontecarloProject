#include <iostream>
#include "muParser.h"

int main(int argc, char *argv[])
{
	try
	{
		double var_a = 1;
		mu::Parser p;
		p.DefineVar("a", &var_a); 
		p.SetExpr("sin(a)");

		for (std::size_t a=0; a<100; ++a)
		{
			var_a = a;  // Change value of variable a
			std::cout << p.Eval() << std::endl;
		}
	}
	catch (mu::Parser::exception_type &e)
	{
		std::cout << e.GetMsg() << std::endl;
	}
	
	return 0;
}