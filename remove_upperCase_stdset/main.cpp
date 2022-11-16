// Write a function that takes a std::set<std::string>* as input and removes all strings that starts with a capital letter, in-place (so the return type is void). For example, "Apple" and "APPLE" should be removed while "aPPLE" and "apple" should remain.

#include <iostream>
#include <set>
#include <iterator>
#include <ostream>

void NoCaps(std::set<std::string> &removeCaps){
    
    std::set<std::string> tempSet;
    for(auto iter = removeCaps.begin(); iter != removeCaps.end(); ++iter){

        std::string checkedString = *iter;
        char firstChar = checkedString.at(0);
        char isUpperCase = toupper(firstChar);

        if (firstChar != isUpperCase){     
            tempSet.insert(checkedString);  
        }
    }
        removeCaps.swap(tempSet);
}

int main() {
  std::cout << "Hello World!\n";

std::set<std::string> test = {"apple", "Cat", "shark"};

NoCaps(test);

for(auto string : test){
    std::cout << string << std::endl;
}

}