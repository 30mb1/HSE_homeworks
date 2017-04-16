#include<iostream>
#include<vector>

using std::cin;

template <typename pointer, typename Type = typename std::iterator_traits<pointer>::value_type>
pointer partition(pointer left, pointer right) {
    Type pivot = *(left + rand() % (right - left));
    pointer j = left;
    long count = 0;
    while (left != right) {
        auto& elem = *left;
        if (elem == pivot) {
            if (count++ % 2 == 0) {
                std::swap(*j++, *left);
            }
        } else if (elem < pivot) {
            std::swap(*j++, *left);
        }
        left++;
    }
    return j;
}


template <typename pointer>
void quicksort(pointer left, pointer right) {
    if (right - left <= 1) {
        return;
    }
    pointer mid = partition(left, right);
    quicksort(left, mid);
    quicksort(mid, right);
}
int main() {
    int N;
    cin >> N;
    std::vector<int> vec1;
    for (auto i = 0; i < N; i++) {
        int buff;
        cin >> buff;
        vec1.push_back(buff);
    }
    if (N > 0) {
        quicksort(vec1.begin(), vec1.end());
        for (int i = 0; i < N; i++) {
            std::cout << vec1[i] << " ";
        }
    }
    return 0;
}
