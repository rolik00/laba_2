#include "help_function.h"

struct Event
{
    int x;
    int startY;
    int endY;
    int status; // 1 - начало прямоугольника, -1 - конец прямоугольника
    Event(int x, int y1, int y2, int st) : x(x), startY(y1), endY(y2), status(st) {}
};

struct Node
{
    int count; // количество прямоугольников на отрезке
    std::shared_ptr<Node> left, right;
    Node(int count, std::shared_ptr<Node> left, std::shared_ptr<Node> right) : count(count), left(left), right(right) {}
    Node() : count(0), left(nullptr), right(nullptr) {}
};

void tree_algo();
