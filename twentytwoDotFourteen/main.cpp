// Copyright (c) 2013 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <queue>
#include <stdexcept>
#include <vector>
#include <stack>
#include <cmath>

using std::cout;
using std::endl;
using std::length_error;
using std::queue;
using std::vector;
using std::stack;
using std::pair;


// TODO: This can be achived with a queue with max.
// TODO: This will be implemented later
//template <class T>
//class Stack
//{
//public:
//    bool Empty(){return elements_.empty();}
//    T Max()
//    {
//      if(Empty())
//        throw length_error("Empty");
//      return cached_max_and_count.top().first;
//    }
//    T Pop()
//    {
//      if(Empty())
//        throw length_error("Empty");
//      else
//      {
//        T popedElement = elements_.pop();
//        if(cached_max_and_count.top().second == 1)
//          cached_max_and_count.pop();
//        else
//        {
//          int* counterRef = &cached_max_and_count.top().second;
//          (*counterRef)--;
//        }
//      }
//    }
//
//private:
//    stack<pair<T,int>> cached_max_and_count;
//    stack<T> elements_;
//};
//template <class T>
//class QueueWithMax
//{
//public:
//    void enqueue(T item){enqueu_.push(item);}
//    T dequeue()
//    {
//      if(dequeue_.empty())
//      {
//        while(!enqueu_.empty())
//        {
//          dequeue_.push(enqueu_.top());
//          enqueu_.pop();
//        }
//      }
//      return dequeue_.pop();
//    }
//
//private:
//    stack<T> enqueu_, dequeue_;
//};

// @include
struct TrafficElement
{
  // Following operators are needed for QueueWithMax with maximum.
  bool operator>(const TrafficElement& that) const {
    return volume > that.volume || (volume == that.volume && time > that.time);
  }

  bool operator==(const TrafficElement& that) const {
    return time == that.time && volume == that.volume;
  }

  bool operator>=(const TrafficElement& that) const {
    return *this > that || *this == that;
  }

  int time;
  double volume;
};

vector<double> CalculateTrafficVolumes(const vector<TrafficElement>& A, int w)
{
  vector<double> results;// we first need to fill in the first w elements
  std::deque<TrafficElement> slidingWindow;
  int index = A[0].time;
  int elementIdx = 0;
  for(int i = 0; i <= A.back().time; i++)
  {
    if(index == i) // a valid input
    {
      while (!slidingWindow.empty() && A[elementIdx].volume >= slidingWindow.back().volume)
      {
          slidingWindow.pop_back(); // 删除没有意义的elements
      }
      slidingWindow.push_back(A[elementIdx++]);
      index = A[elementIdx].time;
    }

    if(!slidingWindow.empty()&&(i - slidingWindow.front().time > w))
      slidingWindow.pop_front(); // 删除过期的elements

    if(slidingWindow.empty()) // 如果当前的sliding window为空,输出0
      results.emplace_back(0);
    else
      results.emplace_back(slidingWindow.front().volume);
  }
  return results;

}
// @exclude
//
//template <typename T>
//bool EqualVector(const vector<T>& A, const vector<T>& B) {
//  return A.size() == B.size() && equal(A.begin(), A.end(), B.begin());
//}

int main(int argc, char* argv[]) {
  int w = 3;
  vector<TrafficElement> A = {TrafficElement{0, 1.3}, TrafficElement{2, 2.5},
                              TrafficElement{3, 3.7}, TrafficElement{5, 1.4},
                              TrafficElement{6, 2.6}, TrafficElement{8, 2.2},
                              TrafficElement{9, 1.7}, TrafficElement{14, 1.1}};

  auto result = CalculateTrafficVolumes(A, w);
  vector<double> golden = { 1.3, 1.3, 2.5, 3.7, 3.7, 3.7,3.7, 2.6, 2.6, 2.6, 2.2, 2.2, 1.7, 0, 1.1};
  assert(golden == result);
  return 0;
}