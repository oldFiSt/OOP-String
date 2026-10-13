#include <iostream>
#include "Stroka.h"

int main()
{
	Stroka text;

	if (text.loadFromFile("D:/Prog_ZAY/my_str/input.txt"))
	{
		text.analyze();
		text.print_Words(Stroka::BY_COUNT);
	}
	else
	{
		std::cout << "Ошибка открытия файла\n";
	}

	return 0;
}