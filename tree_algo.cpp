#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <memory>
#include <chrono>
#include <ctime>
#include "tree_algo.h"

class SegmentTree
{
    std::vector<std::shared_ptr<Node>> roots;
    size_t size;

    void build_segment_tree(const std::vector<int>& values, int left, int right, std::shared_ptr<Node>& node)
    {
        if (right == left)
        {
            node->count = 0;
            return;
        }
        if (left + 1 == right)
        {
            node->count = values[left];
            return;
        }
        int mid = (right + left) / 2;
        if (!node->left) node->left = std::make_shared<Node>();
        build_segment_tree(values, left, mid, node->left);
        if (!node->right) node->right = std::make_shared<Node>();
        build_segment_tree(values, mid, right, node->right);
    }

    auto insert(int status, int left, int right, int curr_left, int curr_right, std::shared_ptr<Node>& node)
    {
        if (curr_left >= left && curr_right <= right)
        {
            return std::make_shared<Node>(node->count + status, node->left, node->right);
        }
        if (curr_left >= right || curr_right <= left || curr_right <= curr_left + 1)
        {
            return node;
        }
        int mid = (curr_left + curr_right) / 2;
        auto left_copy = insert(status, left, right, curr_left, mid, node->left);
        auto right_copy = insert(status, left, right, mid, curr_right, node->right);
        auto new_node = std::make_shared<Node>(node->count, left_copy, right_copy);
        return new_node;
    }

public:
    SegmentTree() = default;

    SegmentTree(const std::vector<int>& values)
    {
        size = values.size();
        roots.push_back(std::make_shared<Node>());
        build_segment_tree(values, 0, values.size(), roots[0]);
    }
    void update(int status, int left, int right)
    {
        auto new_root = insert(status, left, right, 0, size, roots[roots.size() - 1]);
        roots.push_back(new_root);
    }
    int get_ans(int target, int index) {
        auto node = roots[index];
        int ans = 0, left = 0, right = size;
        do {
            ans += node->count;
            int mid = (left + right) / 2;
            if (target < mid) {
                node = node->left;
                right = mid;
            }
            else
            {
                node = node->right;
                left = mid;
            }
        } while (node);
        return ans;
    }
};

class PersistentSegmentTree {
    SegmentTree tree;
    std::vector<int> coordsX, coordsY;
public:
    PersistentSegmentTree(const std::vector<std::vector<int>>& rectangles) {
        std::vector<Event> events;
        std::set<int> help;
        for (const std::vector<int>& rectangle : rectangles)
        {
            events.push_back({ rectangle[0], rectangle[1], rectangle[3], 1 });
            events.push_back({ rectangle[2], rectangle[1], rectangle[3], -1 });
            help.insert(rectangle[1]);
            help.insert(rectangle[3]);
            coordsX.push_back(rectangle[0]);
            coordsX.push_back(rectangle[2]);
        }
        std::sort(events.begin(), events.end(), [](Event e1, Event e2) {return e1.x < e2.x; });
        std::sort(coordsX.begin(), coordsX.end());
        coordsY = std::vector<int>(help.begin(), help.end());
        tree = SegmentTree(std::vector<int>(coordsY.size(), 0));
        for (const Event& event : events)
        {
            int y1 = (std::upper_bound(coordsY.begin(), coordsY.end(), event.startY) - coordsY.begin() - 1);
            int y2 = (std::upper_bound(coordsY.begin(), coordsY.end(), event.endY) - coordsY.begin() - 1);
            tree.update(event.status, y1, y2);
        }
    }

    int get_answer(int x, int y)
    {
        int x_ind = (std::upper_bound(coordsX.begin(), coordsX.end(), x) - coordsX.begin());
        int y_ind = (std::upper_bound(coordsY.begin(), coordsY.end(), y) - coordsY.begin() - 1);
        return tree.get_ans(y_ind, x_ind);
    }
};

void tree_algo() {
    std::vector<int> num_rects = { 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048 }; // количество прямоугольников
    for (int N : num_rects)
    {
        std::vector<std::vector<int>> rectangles = create_rectangles(N);
        std::vector<std::vector<int>> points = create_points(N);

        // preprocessing
        auto start_preproc = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        PersistentSegmentTree tree(rectangles);
        auto end_preproc = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();

        // query processing
        auto start_query = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        for (std::vector<int> point : points)
        {
            int x = point[0], y = point[1];
            int ans = tree.get_answer(x, y);
            // Выводим количество прямоугольников, которым принадлежит данная точка
            //std::cout << ans <<"\n"; 
        }
        auto end_query = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
        std::cout << N << ":\n";
        std::cout << "preprocessing: " << end_preproc - start_preproc << "\n";
        std::cout << "query processing: " << end_query - start_query << "\n";
        std::cout << "total: " << end_query - start_preproc << "\n";
    }
}
