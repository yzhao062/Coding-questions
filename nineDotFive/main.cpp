// Copyright (c) 2015 Elements of Programming Interviews. All rights reserved.

#include <cassert>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>



using std::cout;
using std::endl;
using std::stack;
using std::unique_ptr;
using std::vector;


template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// @include
template <typename T>
struct BSTNode {
	T data;
	unique_ptr<BSTNode<T>> left, right;
};

// @include
vector<int> BSTInSortedOrder(const unique_ptr<BSTNode<int>>& tree)
{
	vector<int> results;
	stack<BSTNode<int>*> nodeStack;
	BSTNode<int>* curr = tree.get();

	while(curr||!nodeStack.empty()) //注意此处的 ||而不是&&
	{
		if(curr == nullptr)
		{
			curr = nodeStack.top(); // 从stack上拿一个点, 问题在于还会被check left
			nodeStack.pop();
			results.emplace_back(curr->data);
			curr = curr->right.get();
		}
		else
		{
			if (curr->left != nullptr)//可以向左边下降
			{
				nodeStack.push(curr);//把current这个加到 stack上
				curr = curr->left.get();// 向左下降
			}
			else// 如果左边是 null,那么需要看看右边是什么情况
			{
				results.emplace_back(curr->data);// 加到结果上
				curr = curr->right.get();
			}
		}
	}
	return results;
}
// @exclude

void SimpleTest() {
	unique_ptr<BSTNode<int>> tree =
			                         make_unique<BSTNode<int>>(BSTNode<int>{43, nullptr});
	auto result = BSTInSortedOrder(tree);
	vector<int> golden_result = {43};
	assert(golden_result.size() == result.size() &&
	       equal(golden_result.begin(), golden_result.end(), result.begin()));
	tree->left = make_unique<BSTNode<int>>(BSTNode<int>{23, nullptr});
	result = BSTInSortedOrder(tree);
	golden_result = {23, 43};
	assert(golden_result.size() == result.size() &&
	       equal(golden_result.begin(), golden_result.end(), result.begin()));
}

int main(int argc, char* argv[]) {
	SimpleTest();
	//        43
	//    23     47
	//      37      53
	//    29  41
	//     31
	unique_ptr<BSTNode<int>> tree =
			                         make_unique<BSTNode<int>>(BSTNode<int>{43, nullptr});
	tree->left = make_unique<BSTNode<int>>(BSTNode<int>{23, nullptr});
	tree->left->right = make_unique<BSTNode<int>>(BSTNode<int>{37, nullptr});
	tree->left->right->left =
			make_unique<BSTNode<int>>(BSTNode<int>{29, nullptr});
	tree->left->right->left->right =
			make_unique<BSTNode<int>>(BSTNode<int>{31, nullptr});
	tree->left->right->right =
			make_unique<BSTNode<int>>(BSTNode<int>{41, nullptr});
	tree->right = make_unique<BSTNode<int>>(BSTNode<int>{47, nullptr});
	tree->right->right = make_unique<BSTNode<int>>(BSTNode<int>{53, nullptr});
	auto result = BSTInSortedOrder(tree);
	vector<int> golden_res = {23, 29, 31, 37, 41, 43, 47, 53};
	assert(golden_res.size() == result.size() &&
	       equal(golden_res.begin(), golden_res.end(), result.begin()));
	return 0;
}