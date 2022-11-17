////non-std implementation of a merge sort 

#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

namespace nonstd{

 template <typename Comparable>
 void sort(std::vector<Comparable>& comparables){
     
     MergeSort(comparables);
 }
}
template <typename T>
void  PrintVector(vector<T>& vector){
    for (auto &cur : vector){
        std::cout << cur << std::endl;
    }
}

template <typename T>
void MergeVectors(std::vector<T>& vector, std::vector<T>& subVectorOne, std::vector<T>& subVectorTwo){
    
    auto vectorOneSize = subVectorOne.size();
    auto vectorTwoSize = subVectorTwo.size();
    
    //track position in sub vectors
    size_t pos1 = 0;
    size_t pos2 = 0;
    
    while(pos1 < vectorOneSize && pos2 < vectorTwoSize){
        
        if(subVectorOne.at(pos1) < subVectorTwo.at(pos2)){
            vector.push_back(subVectorOne.at(pos1++));
        }
           else{
            vector.push_back(subVectorTwo.at(pos2++));
        }
    }
    
    while(pos1 < vectorOneSize) {
        vector.push_back(subVectorOne.at(pos1++));
    }
    while(pos2 < vectorTwoSize){
        vector.push_back(subVectorTwo.at(pos2++));
    }
}
template <typename T>
void MergeSort(std::vector<T>& vector){
    
    //current vector only contains one element
    //cannot be sorted further
    if(vector.size() <= 1){
        return;
    }
    
    auto middle = vector.begin() + (vector.size()/2);
    
    
    std::vector<T> subVectorOne(vector.begin(), middle); // left half of vector
    std::vector<T> subVectorTwo(middle, vector.end());   // right half of vector

    //recursive sort calls will further sub divide the vector until only 1 element
    MergeSort(subVectorOne);
    MergeSort(subVectorTwo);
    
    //clear main vector in order to merge sorted subvectors back in
    vector.clear();


    //call to function that does the merging
    MergeVectors(vector, subVectorOne, subVectorTwo);
        
}


