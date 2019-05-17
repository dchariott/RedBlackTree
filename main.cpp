#include <iostream>
#include "RedBlackTree.h"
#include <vector>

int main() {
    RedBlackTree<int> tree;
    vector<int> nums = {5,3,8,4,2,10,11,15,20,21,23,25,30};
    vector<int> nums2 = {};
    int i = 0;
    tree.MassInsert(nums);
    for (auto num : nums){
        Node<int>* node = tree.Find(num);
        nums2.push_back(node->key);
        cout << "Accessing via vector: " << nums2[i] << endl;
        cout << "Accessing using [] [" << num << "] -> " << tree[num]->key << endl;
        i++;
    }
    tree.InOrderTraversal();
    if (tree.IsBalanced()){
        cout << "Balanced Tree." << endl;
    }
    else{
        cout << "Unbalanced Tree." << endl;
    }
    return 0;
}