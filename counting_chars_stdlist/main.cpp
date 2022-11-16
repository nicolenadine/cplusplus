// Write a function that takes an std::ifstream& as input and returns an std::map, mapping from each character in the input to the number of times that character appeared in the input.

#include <iostream>
#include <fstream>
#include <map>

std::map<char, int>CountingChars(std::ifstream& inputChars){
    std::map<char, int> countedMap;
    char curChar;

    while(!inputChars.eof()){
        
        inputChars >> curChar; 
        
        if(inputChars.eof()){
            break;
        }
        
        auto attemptInsert = countedMap.insert(std::pair<char,int>(curChar, 1));
        
        std::cout << attemptInsert.second << std::endl;
        if(!(attemptInsert.second)){
            ++countedMap[curChar];
        }           
    }
    return countedMap;
}

int main() {

  std::ifstream test("samplechars.txt");

  std::map<char, int> testMap = CountingChars(test);

  for(auto iter = testMap.begin(); iter != testMap.end(); ++iter){
      std::cout << iter->first << " " << iter->second << std::endl;
  }
 

} 