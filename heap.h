#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
// find best child (for loop, start left and assume left is best child, this is also where you would use M)
// check if left most index is greater than or equal to size of array
// compare
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  
  // returns the largest/smallest value in heap
  int sortSiblings (int index) const;


  std::vector<T> data;
  int m_;
  PComparator c_;

};

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c){
  m_ = m;
  c_ = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){}

template <typename T, typename PComparator>
int Heap<T,PComparator>::sortSiblings (int index) const{
  int best = index;

    for (int i = 1; i <= m_; ++i){
      if ((i != m_) && c_(data[index+i],data[best])){
        best = index+i;
      }
    }   

  return best;  
}

// Add implementation of member functions here

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
  return data.size();
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
  if (data.size()==0){
    return true;
  }
  else {
    return false;
  }
}


// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("stack underflow_error"); 

  }
  else{
    return data[0];

  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

}
// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(data.empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("stack underflow_error"); 
  }
  else{
    T temp = data[0];
    data[0] = data.back();
    data.at(data.size()-1) = temp;
    data.pop_back();
      
    for (int i = 2; i < data.size(); i += (i*m_) + (m_%2) ){
      int best = sortSiblings(i); // gets index of best integer
      T temp = data[i];
      data[i] = data[best];
      data[best] = temp;
    }
  }
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item){
  data.push_back(item);
  int itemIndex = size()-1;
  int parent = ( (itemIndex-1) / m_) - (m_ % 2);
  
  while( (parent >=size() ) && (c_(data[itemIndex], data[parent])) ){
    T temp = data[parent];
    data[parent] = data[itemIndex];
    data[itemIndex] = temp;
    itemIndex = parent;
    parent = ( (itemIndex-1) / m_) - (m_ % 2);
  }
  

  }




#endif

