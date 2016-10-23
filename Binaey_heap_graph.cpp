#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

class Heap {
public:
    Heap(int size, int temp = 0) {
        for (size_t ii = 0; ii < size; ++ii) {
            queue.push_back(std::make_pair(ii, temp));
            key_arr.push_back(ii);
        }
        build_heap();
    }
    template <typename T>
    Heap(T begin, T end) {
        size_t xx = 0;
        for (auto ii = begin; ii < end; ++ii, ++xx) {
            queue.push_back(std::make_pair(xx, *ii));
            key_arr.push_back(xx);
        }
        build_heap();
    }
    Heap(std::initializer_list<int> list) {
        size_t ii = 0;
        for (auto xx : list) {
            queue.push_back(std::make_pair(ii, xx));
            key_arr.push_back(ii);
            ii++;
        }
        build_heap();
    }

    const int size() const {
        return queue.size();
    }

    const bool empty() const {
        return (queue.size() == 0);
    }

    const size_t top() const {
        return queue[0].first;
    }

    void pop() {
        std::swap(key_arr[queue[0].first], key_arr[queue[queue.size() - 1].first]);
        queue[0] = queue[queue.size() - 1];
        queue.pop_back();
        Heapify(0);
    }

    void decrease_key(size_t keyy, int value) {
        queue[key_arr[keyy]].second = value;
        size_t key = key_arr[keyy];
        while (key > 0 && queue[(key - 1) / 2].second > queue[key].second) {
            std::swap(key_arr[queue[(key - 1) / 2].first], key_arr[queue[key].first]);
            std::swap(queue[(key - 1) / 2], queue[key]);
            key = (key - 1) / 2;
        }
    }

private:
    std::vector<std::pair<size_t, int>> queue;
    std::vector<size_t> key_arr;
    void build_heap() {
        for (int ii = queue.size() / 2; ii >= 0; --ii) {
            Heapify(ii);
        }
    }

    void Heapify(int ii) {
        for (;;) {
            int leftChild = 2 * ii + 1;
            int rightChild = 2 * ii + 2;
            int largestChild = ii;

            if (leftChild < queue.size() &&
                queue[leftChild].second < queue[largestChild].second) {
                largestChild = leftChild;
            }

            if (rightChild < queue.size() &&
                queue[rightChild].second < queue[largestChild].second) {
                largestChild = rightChild;
            }

            if (largestChild == ii) break;

            std::swap(key_arr[queue[largestChild].first], key_arr[queue[ii].first]);
            std::swap(queue[largestChild], queue[ii]);
            ii = largestChild;
        }
    }
};

int calculate_min_cost() {
    int num, mum;
    std::cin >> num >> mum;
    std::vector<std::vector<std::pair<int, int>>> edges(num);
    for (auto ii = 0; ii < mum; ++ii) {
        int town_one, town_two;
        std::cin >> town_one >> town_two;
        edges[town_one - 1].push_back(std::make_pair(town_two - 1, 0));
        edges[town_two - 1].push_back(std::make_pair(town_one - 1, 0));
    }
    int more_mum;
    std::cin >> more_mum;
    for (auto ii = 0; ii < more_mum; ++ii) {
        int town_one, town_two, price;
        std::cin >> town_one >> town_two >> price;
        edges[town_one - 1].push_back(std::make_pair(town_two - 1, price));
        edges[town_two - 1].push_back(std::make_pair(town_one - 1, price));
    }
    int start, finish;
    std::cin >> start >> finish;
    start--;
    finish--;
    std::vector<int> dist(num, 2000000000);
    dist[start] = 0;
    Heap kuchka(dist.begin(), dist.end());

    while (!kuchka.empty()) {
        size_t cur = kuchka.top();
        if (cur == finish && dist[cur] == 2000000000) return -1;
        if (cur == finish) return dist[cur];
        kuchka.pop();
        for (size_t ii = 0; ii < edges[cur].size(); ++ii) {
            if (dist[edges[cur][ii].first] > dist[cur] + edges[cur][ii].second) {
                dist[edges[cur][ii].first] = dist[cur] + edges[cur][ii].second;
                kuchka.decrease_key(edges[cur][ii].first, dist[cur] + edges[cur][ii].second);
            }
        }
    }
}