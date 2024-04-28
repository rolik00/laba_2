#pragma once
#include <vector>
#include <algorithm>

int power(int x, int y, int n);
std::vector<std::vector<int>> create_rectangles(int n);
std::vector<std::vector<int>> create_points(int n);
int checked(const std::vector<int>& rectangle, int x, int y);
std::vector<int> compressed_coords(const std::vector<std::vector<int>>& rectangles, char type);
std::vector<std::vector<int>> create_matrix(const std::vector<std::vector<int>>& rectangles, const std::vector<int>& coordsX, const std::vector<int>& coordsY);
int binary_search(const std::vector<int>& coords, int target);