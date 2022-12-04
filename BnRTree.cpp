#include "BnRTree.h"

//BnRTree
BnRTree::TreeNode *BnRTree::getRoot() {
    return root;
}

//INSERT
//INSERT
void BnRTree::insert(int value, string id) {
    cout << "insert" << endl;
    root = helpInsert(root, value, id);
    //root->red = false;
    //balance(root);
    print();
}
BnRTree::TreeNode *BnRTree::helpInsert(BnRTree::TreeNode* head, int value, string id) {
    //input root as head
    if (head == nullptr){
        return new TreeNode(value, id);
    }
    if (value == head->value){
        head->IDs.push_back(id);
        return root;
    }
    //for non-empty trees -> insert left or right
    if (value < head->value){
        head->left = helpInsert(head->left, value, id);
    }
    else{
        head->right = helpInsert(head->right, value, id);
    }

    cout << "node: " << head->value << endl;

    //DO ALL THIS AFTER INSERTING
    //parent
    if (head->left != nullptr){
        head->left->parent = head;
    }
    if (head->right != nullptr){
        head->right->parent = head;
    }

    //balance
    if (head->parent == nullptr){//root, make it black
        head->red = false;
    }
    else{
        TreeNode* dad = head->parent;
        if (dad->right == head){
            //cout << "right" << endl;
            dad->right = rotate(head);
        }
        if (dad->left == head){
            //cout << "left" << endl;
            dad->left = rotate(head);
        }
    }
    //rotate unbalanced
    if (unbalanced != nullptr){
        if (right1 & right2){//right, right
            rotateLeft(unbalanced);
        }
        else if (!right1 & right2){//left, right
            rotateLeftRight(unbalanced);
        }
        else if(right1 & !right2){//right, left
            rotateRightLeft(unbalanced);
        }
        else{//left, left
            rotateRight(unbalanced);
        }
        unbalanced = nullptr;
    }

    print();

    return head; //returns root bc stack goes down to first
}

//ROTATE
BnRTree::TreeNode *BnRTree::rotate(BnRTree::TreeNode *head) {
    cout << "hi" << endl;
    //Case 0: if parent black, just return the red node
    if (head->parent->red == false || head->parent->parent == nullptr){
        return head;
    }
    //find uncle
    TreeNode* uncle;
    bool uncleRed;
    if(head->parent->parent->right == head->parent){ //right parent
        uncle = head->parent->parent->left;
        if (uncle == nullptr){ //if uncle is null, it's black
            uncleRed = false;
        }
        else{
            uncleRed = uncle->red;
        }
    }
    else{ //left parent
        uncle = head->parent->parent->right;
        if (uncle == nullptr){ //if uncle is null, it's black
            uncleRed = false;
        }
        else{
            uncleRed = uncle->red;
        }
    }

    //Case 1: if uncle red
    if (uncleRed == true){
        cout << "uncle Red" << endl;
        TreeNode* grandfather = head->parent->parent;
        //grandfather turn red and the 2 children turn black
        grandfather->red = true;
        grandfather->right->red = false;
        cout << grandfather->right->red << endl;
        grandfather->left->red = false;
        return head;
    }
    //Case 2: if uncle black
    else{
        cout << "uncle Black" << endl;
        TreeNode* grandfather = head->parent->parent;
        TreeNode* dad = head->parent;
        if (grandfather->right == head->parent){
            right1 = true;
        }
        else{
            right1 = false;
        }
        if (dad->right == head){
            right2 = true;
        }
        else{
            right2 = false;
        }
        unbalanced = grandfather;
    }
    return head;
}


BnRTree::TreeNode *BnRTree::rotateRight(BnRTree::TreeNode *head) {
    //left child, then left grandchild
    TreeNode* child = head ->left;
    TreeNode* grandchild = child->left;
    //head point child's left
    head->left = child -> right;
    //child point head right and grandchild left
    child -> right = head;

    return child; //the new head
}

BnRTree::TreeNode *BnRTree::rotateLeft(BnRTree::TreeNode *head) {
    //right child, then right grandchild
    TreeNode* child = head ->right;
    TreeNode* grandchild = child->right;
    //head point child's left
    head->right = child -> left;
    //child point head left and grandchild right
    child -> left = head;

    return child; //the new head
}

BnRTree::TreeNode *BnRTree::rotateLeftRight(BnRTree::TreeNode *head) {
    //left child, then right grandchild
    TreeNode* child = head ->left;
    TreeNode* grandchild = child ->right;
    //head takes grandchild's right
    head -> left = grandchild -> right;
    //child takes grandchild's left
    child -> right = grandchild -> left;
    //grandchild point left and right
    grandchild -> left = child;
    grandchild -> right = head;

    return grandchild; //the new head
}

BnRTree::TreeNode *BnRTree::rotateRightLeft(BnRTree::TreeNode *head) {
    //right child, then left grandchild
    TreeNode* child = head ->right;
    TreeNode* grandchild = child ->left;
    //head takes grandchild's left
    head -> right = grandchild -> left;
    //child takes grandchild's right
    child -> left = grandchild -> right;
    //grandchild point left and right
    grandchild -> right = child;
    grandchild -> left = head;

    return grandchild; //the new head
}


//PRINT
void BnRTree::helpPrint(const std::string &prefix, TreeNode *node, bool isLeft) {
    if( node != nullptr ){
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        string color;
        if (node->red){
            color = "R";
        }
        else{
            color = "B";
        }
        std::cout << node->value << " " << color << std::endl;

        // enter the next tree level - left and right branch
        helpPrint( prefix + (isLeft ? "│   " : "    "), node->left, true);
        helpPrint( prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

void BnRTree::print(){
    helpPrint("", root, false);
}



