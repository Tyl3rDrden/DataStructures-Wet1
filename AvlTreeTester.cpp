#include "AVLTREE.h"
#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
struct GreaterThan {
    bool operator()(const int& a, const int& b) const {
        return b >= a;
    }
};
std::vector<int> generatePermutation(int N) {
    // Create a vector with values 1 to N
    std::vector<int> v(N);
    for (int i = 0; i < N; ++i) {
        v[i] = i + 1;
    }

    // Obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Shuffle the vector to generate a permutation
    std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));

    return v;
}
int main() {
    GreaterThan gt;
    int N = 10;
    std::vector<int> permuation  = generatePermutation(N);
    int* arr = permuation.data();
    AVLTREE<int, GreaterThan, int> tree(gt);
    int one = 1, two =2, three =3;
    for (int i = 0; i < N; i++)
    {
        tree.InsertElement(std::make_shared<int>(i), arr + i);
    }
    /*permuation  = generatePermutation(N);
    for (int i = 0; i < N-100; i++)
    {
        tree.RemoveElement(permuation[i]);
    }*/
    //std::cout << *(tree.Find(1));
    tree.printVisual();
    //tree.RemoveElement(2);
    //std::cout << "Tree Didn't Explode";
    //tree.InsertElement(std::make_shared<int>(40));
    return 0;
}