#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef vector<int>::iterator kek;
void sort_or_death(kek begin1, kek end1, kek begin2, kek end2, vector<int>& finalvec) {
    if (begin1 == end1 || begin2 == end2) {
        if (begin1 == end1) {
            finalvec.push_back(*begin2);
            ++begin2;
        } else if (begin2 == end2) {
            finalvec.push_back(*begin1);
            ++begin1;
        }
    } else if (*begin1 <= *begin2) {
        finalvec.push_back(*begin1);
        ++begin1;
    } else if (*begin2 < *begin1) {
        finalvec.push_back(*begin2);
        ++begin2;
    }
    if (begin1 != end1 || begin2 != end2) {
        sort_or_death(begin1, end1, begin2, end2, finalvec);
    }
}
vector<int> sort_or_death(vector<int>& finalvec) {
    if (finalvec.size() <= 1)
        return finalvec;
    vector<int> left, right, Vec;
    int middle = (finalvec.size() + 1) / 2;

    for (int i = 0; i < middle; i++) {
        left.push_back(finalvec[i]);
    }

    for (int i = middle; i < finalvec.size(); i++) {
        right.push_back(finalvec[i]);
    }

    left = sort_or_death(left);

    right = sort_or_death(right);

    sort_or_death(left.begin(), left.end(), right.begin(), right.end(), Vec);

    return Vec;
}


int main() {
    int N, N1;
    cin >> N;
    vector<int> vec1;
    for (auto i = 0; i < N; i++) {
        int buff;
        cin >> buff;
        vec1.push_back(buff);
    }
    vec1 = sort_or_death(vec1);
    for (auto x : vec1) {
        cout << x << " ";
    }
    return 0;
}
