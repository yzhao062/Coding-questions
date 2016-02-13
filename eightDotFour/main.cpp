// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::make_shared;
using std::shared_ptr;

template <typename T>
struct ListNode {
  T data;
  shared_ptr<ListNode<T>> next;
};

int getLength(const shared_ptr<ListNode<int>>& head)
{
  shared_ptr<ListNode<int>> temp = head;
  int counter = 0;
  while(temp != nullptr)
  {
    counter ++;
    temp = temp->next;
  }
  return counter;
}
// @include
shared_ptr<ListNode<int>> HasCycle(const shared_ptr<ListNode<int>>& head)
{
  shared_ptr<ListNode<int>> fast = head;
  shared_ptr<ListNode<int>> slow = head;

  int cycleLength = 1; // default value
  while(fast->next != nullptr && fast->next->next != nullptr)
  {
    fast = fast->next->next;
    slow = slow->next;

    if(fast == slow) //  found cycle
    {
      while(fast->next != slow)
      {
         fast = fast -> next;
         cycleLength++;
      }

      slow = head; // 二次利用代码
      fast = head; // ...

      while(cycleLength--)
        fast = fast->next;

      while(fast != slow)
      {
        fast = fast -> next;
        slow = slow -> next;
      }
      return slow;
    }
  }
  return nullptr;// no cycle

}
// @exclude

int main(int argc, char* argv[]) {
  shared_ptr<ListNode<int>> L3 =
      make_shared<ListNode<int>>(ListNode<int>{3, nullptr});
  shared_ptr<ListNode<int>> L2 =
      make_shared<ListNode<int>>(ListNode<int>{2, L3});
  shared_ptr<ListNode<int>> L1 =
      make_shared<ListNode<int>>(ListNode<int>{1, L2});

  // should output "L1 does not have cycle."
  assert(HasCycle(L1) == nullptr);
  cout << "L1 " << (HasCycle(L1) ? "has" : "does not have") << " cycle."
       << endl;

  // make it a cycle
  L3->next = L2;
  // should output "L1 has cycle, located at node has value 2"
  assert(HasCycle(L1) != nullptr);
  assert(HasCycle(L1)->data == 2);
  auto temp = HasCycle(L1);
  if (temp) {
    cout << "L1 has cycle, located at node has value " << temp->data << endl;
  } else {
    cout << "L1 does not have cycle" << endl;
  }
  return 0;
}