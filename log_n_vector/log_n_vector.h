// log_n_vector is a class that behaves like std::vector but without the O(n) push_back.
// Whenever it runs out of space, a new array of double the size is allocated
// but instead of copying all the old elements to it, it keeps all the current elements
// where they are and stores new ones in the new array until it's full.

#ifndef _log_n_vector_h_
#define _log_n_vector_h_

#include <cmath>
#include <memory>
#include <vector>
#include <string>

using namespace std;

template <typename T>
class LogNVector {

  std::vector<std::unique_ptr<T[]>> arrays_;
  int size_, capacity_;

public:
  LogNVector() {
      size_ = capacity_ = 0;

  }
  LogNVector(const LogNVector& other) : LogNVector() {

      int sizeToCopy = other.size();
      
      for(int i = 0; i < sizeToCopy; ++i){
          this->push_back(other[i]);
      }
  }
  LogNVector(std::initializer_list<T> ilist) : LogNVector() {
      
      typename std::initializer_list<T>::iterator curItem;
      
      for(curItem = ilist.begin(); curItem != ilist.end(); curItem++){
          this->push_back(*curItem);

      }
  }
  ~LogNVector() {
 
  }


  int size() const noexcept {
      return this->size_;
  }
  int capacity() const noexcept {
      return this->capacity_;
  }
  void push_back(const T& value){
      
      if (size_ == capacity_){
          makeNewArray();
      }
      
      int firstIndex;
      int secondIndex;
      
      firstIndex = this->sizeMinusOne();
      secondIndex = this->size_ - getConsecMaxArrSize(firstIndex - 1);
      
      this->arrays_[firstIndex][secondIndex] = value;
      size_ += 1;
          
  }
 
    void makeNewArray(){
        
        capacity_ +=  pow(2,(log2(size()+1)));
        this->arrays_.emplace_back(new T[capacity_ + 1 ]);
    
    }
    
  //convert single index value into a 2D index.
  const T& operator[](int index) const {
     
      int firstIndex = (log2(index + 1));
      int secondIndex = (index + 1) - pow(2, firstIndex);
            
      return this->arrays_[firstIndex][secondIndex];
  }
    
  T& operator[](int index) {
     
      int firstIndex = (log2(index + 1));
      int secondIndex = (index + 1) - pow(2, firstIndex);
            
      return this->arrays_[firstIndex][secondIndex];
  }

private:
    void makeNewtArray()
    {

        int nextSize = getArrMaxSize( sizeMinusOne() + 1 );
        this->arrays_.emplace_back(new T[nextSize]);
        this->capacity_ += nextSize;
    }

    int sizeMinusOne() const
    {
        return this->arrays_.size() - 1;

    }

    int getArrMaxSize(int num) const
    {
        if(num < 0)
            return 0;
        return exp2(num);
    }

    int getConsecMaxArrSize(int num) const
    {
        int total = 0;
        for (int k = 0; k <= num; k++)
            total += getArrMaxSize(k);
        return total;
    }
};

#endif // _log_n_vector_h_
