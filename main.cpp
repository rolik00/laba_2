#include <iostream>
#include "naive_algo.h"
#include "map_algo.h"
#include "tree_algo.h"

int main()
{
	std::cout << "ÀËÃÎÐÈÒÌ ÏÅÐÅÁÎÐÀ:\n";
	naive_algo();
	std::cout << "ÀËÃÎÐÈÒÌ ÍÀ ÊÀÐÒÅ:\n";
	map_algo();
	std::cout << "ÀËÃÎÐÈÒÌ ÍÀ ÏÅÐÑÈÑÒÅÍÒÍÎÌ ÄÅÐÅÂÅ ÎÒÐÅÇÊÎÂ:\n";
	tree_algo();
	return 0;
}