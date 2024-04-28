#include <iostream>
#include <chrono>
#include <ctime>
#include "map_algo.h"

void map_algo()
{
    std::vector<int> num_rects = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048}; // количество пр€моугольников
    for (int N : num_rects)
    {
        std::vector<std::vector<int>> rectangles = create_rectangles(N);
        std::vector<std::vector<int>> points = create_points(N);

        // preprocessing
        auto start_preproc = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        std::vector<int> coordsX = compressed_coords(rectangles, 'x');
        std::vector<int> coordsY = compressed_coords(rectangles, 'y');
        std::vector<std::vector<int>> matrix = create_matrix(rectangles, coordsX, coordsY);
        auto end_preproc = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        int n = coordsY.size(), m = coordsX.size();

        // query processing
        auto start_query = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        for (std::vector<int> point : points)
        {
            int x = binary_search(coordsX, point[0]), y = binary_search(coordsY, point[1]);
            // ¬ыводим количество пр€моугольников, которым принадлежит данна€ точка
            //if (x != -1 && y != -1) std::cout << "(" << point[0] << ", " << point[1] << "): "<< matrix[y][x] <<"\n"; 
            //else  std::cout << "(" << point[0] << ", " << point[1] << "): "<< 0 <<"\n";
        }
        auto end_query = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        std::cout << N << ":\n";
        std::cout << "preprocessing: " << end_preproc - start_preproc << "\n";
        std::cout << "query processing: " << end_query - start_query << "\n";
        std::cout << "total: " << end_query - start_preproc << "\n";
    }
}