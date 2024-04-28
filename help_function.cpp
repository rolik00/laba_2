#include "help_function.h"

int power(int x, int y, int n)
{
    if (y == 0) return 1;
    int z = power(x % n, y / 2, n) % n;
    if (y % 2 == 0) return (z * z) % n;
    else return ((x % n) * ((z * z) % n)) % n;
}

std::vector<std::vector<int>> create_rectangles(int n)
{
    std::vector<std::vector<int>> rect = {};
    for (int i = 0; i < n; i++)
    {
        rect.push_back({ 10 * i, 10 * i, 10 * (2 * n - i), 10 * (2 * n - i) });
    }
    return rect;
}

std::vector<std::vector<int>> create_points(int n)
{
    int p_x = 283, p_y = 191, x, y;
    std::vector<std::vector<int>> points;
    for (int i = 0; i < 2 * n; i++)
    {
        x = power(p_x * i, 31, 20 * n);
        y = power(p_y * i, 31, 20 * n);
        points.push_back({ x, y });
    }
    return points;
}

int checked(const std::vector<int>& rectangle, int x, int y)
{
    if ((rectangle[0] <= x) && (x < rectangle[2]) && (rectangle[1] <= y) && (y < rectangle[3])) return 1;
    return 0;
}

std::vector<int> compressed_coords(const std::vector<std::vector<int>>& rectangles, char type)
{
    std::vector<int> coords;
    for (std::vector<int> rectangle : rectangles)
    {
        int i = 0;
        if (type == 'y') i++;
        for (i; i < 4; i += 2)
        {
            coords.push_back(rectangle[i]);
        }
    }
    sort(coords.begin(), coords.end());
    coords.erase(std::unique(coords.begin(), coords.end()), coords.end());
    return coords;
}

std::vector<std::vector<int>> create_matrix(const std::vector<std::vector<int>>& rectangles, const std::vector<int>& coordsX, const std::vector<int>& coordsY)
{
    int n = coordsY.size(), m = coordsX.size();
    std::vector<std::vector<int>> matrix(n, std::vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int y = coordsY[i], x = coordsX[j], ans = 0;
            for (std::vector<int> rectangle : rectangles)
            {
                ans += checked(rectangle, x, y);
            }
            matrix[i][j] = ans;
        }
    }
    return matrix;
}

int binary_search(const std::vector<int>& coords, int target)
{
    int left = 0, right = coords.size() - 1;
    if (target < coords[left] || target > coords[right]) return -1;
    while (right >= left) {
        int mid = left + (right - left) / 2;
        if (coords[mid] == target) return mid;
        if (coords[mid] > target) right = mid - 1;
        else left = mid + 1;
    }
    return right;
}