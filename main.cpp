#include <iostream>
#include "naive_algo.h"
#include "map_algo.h"
#include "tree_algo.h"

int main()
{
	std::cout << "�������� ��������:\n";
	naive_algo();
	std::cout << "�������� �� �����:\n";
	map_algo();
	std::cout << "�������� �� ������������� ������ ��������:\n";
	tree_algo();
	return 0;
}