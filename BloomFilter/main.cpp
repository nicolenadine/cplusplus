//  main.cpp
//  Bloom filter


#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>

using namespace std;

//hash function to ensure that bloom filter is maintined on subsequence execution.
unsigned long string_hash(const string& str){
    unsigned long result = 0;
    for (char c : str){
        result = 37 * result + c;
    }
    return result;
}

struct BloomFilter{
    
    unsigned char bytes[1024];
    
    BloomFilter(){
        //intitalize all bits to off to start
        for (int i = 0; i< 1024; i++){
            bytes[i] = '0';
        }
    }
    
    // pass lines through filter
    void insert(const string& str){
        unsigned long byte_index = string_hash(str) %  1024;
        bytes[byte_index] = '1'; //parenthesis?
    }
    
    //check to see if a value could be in the file
    //result of 1 means it COULD be in the file
    //result of 0 means is CANNOT be in the file
    bool could_contain(const string& str){
        unsigned long byte_index = string_hash(str) % 1024;
        return bytes[byte_index] == '1';
    }
};


int main(int argc, const char *argv[]) {
  if (argc > 1) { // If file is passed as argv[1]
      ifstream filter_file(argv[1]);
      BloomFilter filter;
      string line;

    // Read in the file to create my filter object
    for (int i = 0; filter_file >> filter.bytes[i] && i < 1024; i++){}
    
    if (!filter_file.eof()){
        throw runtime_error("Error reading from filter file.");
    }
    
    // Output the line if it "passes" the filter
    for (string line; getline(cin, line); ) {
        if (filter.could_contain(line)) {
        cout << line << endl;
        }
    }
  }
    
    else { // If file is passed as argv[1]
      
        BloomFilter filter;
      
        // Read in lines from cin and call filter function
        for (string line; getline(cin, line);) {
            filter.insert(line);
        }
      
        if (!cin.eof()) {
          throw runtime_error("Error reading from cin");
        }
      
        // Output if in filter
       for (int i = 0; i < 1024; i++){
          cout << filter.bytes[i];
       }
    }
  
  return 0;
}
