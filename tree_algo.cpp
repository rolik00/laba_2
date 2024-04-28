#include <iostream>
#include <vector>
#include <functional>
#include <chrono>
#include <ctime>
#include "tree_algo.h"

Node* build_segment_tree(int left, int right)
{
    if (left + 1 == right)
    {
        return new Node(0, left, right, nullptr, nullptr);
    }
    int mid = (left + right) / 2;
    Node* l = build_segment_tree(left, mid);
    Node* r = build_segment_tree(mid, right);
    return new Node(l->count + r->count, l->left_index, r->right_index, l, r);
}

Node* insert(Node* node, int start, int end, int status)
{
    if (start <= node->left_index && node->right_index <= end)
    {
        return new Node(node->count + status, node->left_index, node->right_index, node->left, node->right);
    }
    if (node->right_index <= start || end <= node->left_index)
    {
        return node;
    }
    Node* new_node = new Node(node->count, node->left_index, node->right_index, node->left, node->right);
    new_node->left = insert(new_node->left, start, end, status);
    new_node->right = insert(new_node->right, start, end, status);
    return new_node;
}

std::vector<Node*> build_persistent_segment_tree(std::vector<std::vector<int>> rectangles, std::vector<int> coordsY)
{
    int n = coordsY.size();
    std::vector<Event> events;
    for (std::vector<int> rectangle : rectangles)
    {
        Event event_1(rectangle[0], rectangle[1], rectangle[3], 1);
        Event event_2(rectangle[2], rectangle[1], rectangle[3], -1);
        events.push_back(event_1);
        events.push_back(event_2);
    }
    std::function<bool(Event, Event)> compare = [](Event e1, Event e2) {return e1.x < e2.x; };
    sort(events.begin(), events.end(), compare);
    Node* root = build_segment_tree(0, n);
    std::vector<Node*> roots;
    int endX = events[0].x;
    for (Event event : events)
    {
        if (endX != event.x)
        {
            roots.push_back(root);
            endX = event.x;
        }
        int y1 = binary_search(coordsY, event.startY), y2 = binary_search(coordsY, event.endY);
        root = insert(root, y1, y2, event.status);
    }
    roots.push_back(root);
    return roots;
}

int get_number(Node* node, int target)
{
    if (node != nullptr)
    {
        int mid = (node->left_index + node->right_index) / 2;
        if (target < mid) return node->count + get_number(node->left, target);
        else return node->count + get_number(node->right, target);
    }
    return 0;
}

void tree_algo() {
    std::vector<int> num_rects = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 }; // количество пр€моугольников
    for (int N : num_rects)
    {
        std::vector<std::vector<int>> rectangles = create_rectangles(N);
        std::vector<std::vector<int>> points = create_points(N);

        // preprocessing
        auto start_preproc = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        std::vector<int> coordsX = compressed_coords(rectangles, 'x');
        std::vector<int> coordsY = compressed_coords(rectangles, 'y');
        std::vector<Node*> roots = build_persistent_segment_tree(rectangles, coordsY);
        auto end_preproc = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

        // query processing
        auto start_query = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        for (std::vector<int> point : points)
        {
            int x = binary_search(coordsX, point[0]), y = binary_search(coordsY, point[1]);
            // ¬ыводим количество пр€моугольников, которым принадлежит данна€ точка
            //if (x != -1 && y != -1) std::cout << "(" << point[0] << ", " << point[1] << "): "<< get_number(roots[x], y) <<"\n"; 
            //else  std::cout << "(" << point[0] << ", " << point[1] << "): "<< 0 <<"\n";
        }
        auto end_query = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        std::cout << N << ":\n";
        std::cout << "preprocessing: " << end_preproc - start_preproc << "\n";
        std::cout << "query processing: " << end_query - start_query << "\n";
        std::cout << "total: " << end_query - start_preproc << "\n";
    }
}