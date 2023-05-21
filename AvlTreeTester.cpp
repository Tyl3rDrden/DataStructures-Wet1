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
    int N = 10;
    std::vector<int> permuation  = generatePermutation(N);
    int* arr = permuation.data();
    AVLTREE<int, GreaterThan, int> tree;
    int one = 1, two =2, three =3;
    for (int i = 0; i < N; i++)
    {
        tree.InsertElement(std::make_shared<int>(i), arr + i);
    }
    //tree.printVisual();
    std::cout << "________________________";
    std::vector<int> permuation1  = generatePermutation(N);
    /*for (int i = 0; i < 99996 ;i++)
    {
        //std::cout << permuation1[i] << " \n"; 
        tree.RemoveElement(permuation1[i]);
    }*/
    //tree.RemoveElement(70);
    

    //std::cout << *(tree.Find(1));
    //int* arr1 = tree.GetKeysDescending();
    //for (int i = 0; i < tree.getSize(); i++)
    //{
    //    std::cout << arr1[i]<< " ";
        /* code */
    //}
    //delete[] arr1;
    if(tree.ElementInTree(10))
    {
        std::cout << "Found "; 

    }
    tree.printVisual();
    //tree.RemoveElement(2);
    std::cout << tree.getMaxElement();
    std::cout << "_________________________";

    int** decendingDatasByKeys = tree.GetDataPtrsDescending();
    for (int i = 0; i < tree.getSize(); i++)
    {
        std::cout << *decendingDatasByKeys[i] << " ";
    }
    
    //tree.InsertElement(std::make_shared<int>(40));
    return 0;
}