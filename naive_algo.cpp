#include <iostream>
#include <chrono>
#include <ctime>
#include "naive_algo.h"

void naive_algo()
{
    std::vector<int> num_rects = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 }; // количество прямоугольников
    for (int N : num_rects)
    {
        std::vector<std::vector<int>> rectangles = create_rectangles(N);
        std::vector<std::vector<int>> points = create_points(N);
        int ans, x, y;
        auto start = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        for (int p = 0; p < points.size(); p++)
        {
            ans = 0, x = points[p][0], y = points[p][1];
            for (std::vector<int> rectangle : rectangles)
            {
                ans += checked(rectangle, x, y);
            }
            //std::cout << "(" << x << ", " << y << "): " << ans << "\n"; // эта строчка выводит количество прямоугольников, которым принадлежит данная точка
        }
        auto end = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        std::cout << N << " " << end - start << "\n";
    }
}