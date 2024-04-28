#pragma once
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
    int left_index;
    int right_index;
    Node* left;
    Node* right;
    Node() : count(0), left_index(0), right_index(0), left(nullptr), right(nullptr) {}
    Node(int count, int l_index, int r_index, Node* l, Node* r) : count(count), left_index(l_index), right_index(r_index), left(l), right(r) {}
};

Node* build_segment_tree(int left, int right);

Node* insert(Node* node, int start, int end, int status);

std::vector<Node*> build_persistent_segment_tree(std::vector<std::vector<int>> rectangles, std::vector<int> coordsY);

int get_number(Node* node, int target);

void tree_algo();