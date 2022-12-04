#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include "Athlete.h"
#pragma once

using namespace std;

//AVL tree class
class BnRTree{
private:
    struct TreeNode{
        int value;
        vector<string> IDs; //athletes could have the same value, so we push_back
        bool red = true;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        TreeNode* parent = nullptr;
        TreeNode(int v, string id){
            value = v;
            IDs.push_back(id);
            left = nullptr;
            right = nullptr;
            red = true;
        }
        //TreeNode(int v, string id) : value(v), IDs(id), left(nullptr), right(nullptr), red(true){};
    };
    TreeNode* root = nullptr;
    TreeNode* unbalanced = nullptr;
    bool right1;
    bool right2;
    BnRTree::TreeNode* helpInsert(BnRTree::TreeNode* head, int value, string id);
public:
    BnRTree::TreeNode* getRoot();
    //insert
    void insert(int value, string id);
    //traversals
    string searchValue(int value); //return ID
    void searchBelow (BnRTree::TreeNode* head);

//    void inOrder(AVL::TreeNode* head, int num);
//    void preOrder(AVL::TreeNode* head, int num);
//    void postOrder(AVL::TreeNode* head, AVL::TreeNode* remove);
//    void postOrderhelp(AVL::TreeNode* head);

    //rotations
    BnRTree::TreeNode* rotate (BnRTree::TreeNode* unbalanced); //return what has to be pointed

    BnRTree::TreeNode* rotateRight(BnRTree::TreeNode* head);
    BnRTree::TreeNode* rotateLeft(BnRTree::TreeNode* head);
    BnRTree::TreeNode* rotateLeftRight(BnRTree::TreeNode* head);
    BnRTree::TreeNode* rotateRightLeft(BnRTree::TreeNode* head);

    //print
    void helpPrint(const std::string& prefix, TreeNode *node, bool isLeft);
    void print();

    //delete
    void destruct(BnRTree::TreeNode* head); //from sum of two levels quiz
    //~BnRTree();

};

class allTrees{
private:
    map<string, Athlete*> idToAthlete; //ID to athlete object(pointer)
    BnRTree treeA;
    BnRTree treeH;
    BnRTree treeW;

public:
    void insertAll();
    void insertAge();
    void insertHeight();
    void insertWeight();
    void findAge();
    void findAthletes(string sport, string gender, int age, int height, int weight);


};
