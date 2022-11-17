// test code for custom merge sort algorithm 
// contained in nonstd_sort.h

#include <vector>
#include "nonstd_sort.h"

using namespace std;

int main()
{
    std::vector<int> vec1{ 43, 5, 123, 43, 94, 359, -23, 2, -1 };

    PrintVector(vec1);
    MergeSort(vec1);
    cout << "-----" << endl;
    PrintVector(vec1);
    
}
    

