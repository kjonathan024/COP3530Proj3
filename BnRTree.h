#include <iostream>
#include <vector>
#include "Athlete.h"
#pragma once
using namespace std;

//AVL tree class
class BnRTree{
private:
    struct TreeNode{
        int value;
        Athlete* athlete;
        bool red = true;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
        TreeNode* parent = nullptr;
        TreeNode(Athlete* a){
            value = stoi(a->getID());
            athlete = a;
            left = nullptr;
            right = nullptr;
            red = true;
        }
        //TreeNode(int v, string id) : value(v), IDs(id), left(nullptr), right(nullptr), red(true){};
    };
    vector<TreeNode*> nodesPassed;
    TreeNode* root = nullptr;
    TreeNode* unbalanced = nullptr;
    bool right1;
    bool right2;
    BnRTree::TreeNode* helpInsert(BnRTree::TreeNode* head, int value, Athlete* a);

public:
    BnRTree::TreeNode* getRoot();
    //insert
    void insert(Athlete* a);
    //traversals
    Athlete* searchID(string ID); //return athlete
    Athlete* helpSearch(BnRTree::TreeNode* head, int value);

    //balance
    void balanceNodes();

    //rotations
    BnRTree::TreeNode* rotate (BnRTree::TreeNode* unbalanced); //return what has to be pointed

    BnRTree::TreeNode* rotateRight(BnRTree::TreeNode* head);
    BnRTree::TreeNode* rotateLeft(BnRTree::TreeNode* head);
    BnRTree::TreeNode* rotateLeftRight(BnRTree::TreeNode* head);
    BnRTree::TreeNode* rotateRightLeft(BnRTree::TreeNode* head);

    
    //delete
    //void destruct(BnRTree::TreeNode* head);
    //~BnRTree();

};