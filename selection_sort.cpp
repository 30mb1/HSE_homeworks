#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void sort_or_death(vector<int>::iterator begin, vector<int>::iterator end) {
    vector<int>::iterator  min = begin;
    for (auto i = begin; i < end; ++i) {
        if (*i < *min) {
            min = i;
        }
    }
    swap(*min, *begin);
    begin++;
    if (begin != end) {
        sort_or_death(begin, end);
    }
}



int main() {
    int N;
    cin >> N;
    if (N != 0) {
        vector<int> Vec;
        for (int i = 0; i < N; i++) {
            int elem;
            cin >> elem;
            Vec.push_back(elem);
        }
        sort_or_death(Vec.begin(), Vec.end());
        for (auto i : Vec) {
            cout << i << " ";
        }
    }
    return 0;
}
