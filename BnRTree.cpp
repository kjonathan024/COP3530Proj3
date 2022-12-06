#include "BnRTree.h"

//BnRTree
BnRTree::TreeNode *BnRTree::getRoot() {
    return root;
}

//SEARCH ID
Athlete *BnRTree::searchID(std::string ID) {
    return helpSearch(root, stoi(ID));
}

Athlete *BnRTree::helpSearch(BnRTree::TreeNode *head, int value) {
    while (value != head->value){
        if (value < head->value){
            head = head->left;
        }
        else{
            head = head->right;
        }
    }
    return head->athlete;
}


//INSERT
//INSERT
void BnRTree::insert(Athlete* a) {
    root = helpInsert(root, stoi(a->getID()), a);
    //balance
    balanceNodes();
    root->red = false;
}

void BnRTree::balanceNodes() {
    //nodesPassed starts from last inserted to root
    unbalanced = nullptr;
    for (int i = 0; i < nodesPassed.size(); ++i) {
        TreeNode* head = nodesPassed.at(i);
        //cout << "node: " << head->value << ", Color: " << head->red << endl;
        //balance
        if (unbalanced == nullptr){
            //cout << "unbalanced is null " << endl;
            if (head->parent == nullptr){//root, make it black
                head->red = false;
            }
            else{
                TreeNode* dad = head->parent;
                if (dad->right == head){
                    dad->right = rotate(head);
                }
                if (dad->left == head){
                    dad->left = rotate(head);
                }
            }
        }


        //rotate unbalanced
        if (unbalanced != nullptr && unbalanced == head){
            //cout << "(rotating) unbalanced: "<< head->value << endl;
            TreeNode* newChild = nullptr;
            if (right1 & right2){//right, right
                //cout << "left rotation" << endl;
                newChild = rotateLeft(unbalanced);
                if (head->parent == nullptr){
                    root = newChild;
                    newChild->parent = nullptr;
                }
                else {
                    TreeNode* dad = head->parent;
                    if (dad->right == head){
                        dad->right = newChild;
                    }
                    if (dad->left == head){
                        dad->left = newChild;
                    }
                    newChild->parent = dad;
                }
                //assign parents
                if (newChild->left != nullptr){
                    newChild->left->parent = newChild;
                }
                if (newChild->right != nullptr){
                    newChild->right->parent = newChild;
                }
            }
            else if (!right1 & right2){//left, right
                //cout << "left right rotation" << endl;
                newChild = rotateLeftRight(unbalanced);
                if (head->parent == nullptr){
                    root = newChild;
                    newChild->parent = nullptr;
                }
                else{
                    TreeNode* dad = head->parent;
                    if (dad->right == head){
                        dad->right = newChild;
                    }
                    if (dad->left == head){
                        dad->left = newChild;
                    }
                    newChild->parent = dad;
                }
                //assign parents
                if (newChild->left != nullptr){
                    newChild->left->parent = newChild;
                }
                if (newChild->right != nullptr){
                    newChild->right->parent = newChild;
                }
            }
            else if(right1 & !right2){//right, left
                //cout << "right left rotation" << endl;
                newChild = rotateRightLeft(unbalanced);
                if (head->parent == nullptr){
                    root = newChild;
                    newChild->parent = nullptr;
                }
                else{
                    TreeNode* dad = head->parent;
                    if (dad->right == head){
                        dad->right = newChild;
                    }
                    if (dad->left == head){
                        dad->left = newChild;
                    }
                    newChild->parent = dad;
                }
                //assign parents
                if (newChild->left != nullptr){
                    newChild->left->parent = newChild;
                }
                if (newChild->right != nullptr){
                    newChild->right->parent = newChild;
                }
            }
            else{//left, left
                //cout << "right rotation" << endl;
                newChild = rotateRight(unbalanced);
                if (head->parent == nullptr){
                    root = newChild;
                    newChild->parent = nullptr;
                }
                else{
                    TreeNode* dad = head->parent;
                    if (dad->right == head){
                        dad->right = newChild;
                    }
                    if (dad->left == head){
                        dad->left = newChild;
                    }
                    newChild->parent = dad;
                }
                //assign parents
                if (newChild->left != nullptr){
                    newChild->left->parent = newChild;
                }
                if (newChild->right != nullptr){
                    newChild->right->parent = newChild;
                }
            }
            unbalanced = nullptr;
            //after rotating, we have to modify the colors
            //newChild at top turns black and the 2 children turn red
            newChild->red = false;
            newChild->right->red = true;
            newChild->left->red = true;
        }
    }
    nodesPassed.clear();
}

BnRTree::TreeNode *BnRTree::helpInsert(BnRTree::TreeNode* head, int value, Athlete* a) {
    //input root as head
    if (head == nullptr){
        return new TreeNode(a);
    }
    //for non-empty trees -> insert left or right
    if (value < head->value){
        head->left = helpInsert(head->left, value, a);
    }
    else{
        head->right = helpInsert(head->right, value, a);
    }

    //DO ALL THIS AFTER INSERTING

    //parent
    if (head->left != nullptr){
        head->left->parent = head;
    }
    if (head->right != nullptr){
        head->right->parent = head;
    }

    //stack: starting from last/inserted node's parent and going up
    //find last node
    TreeNode* last = nullptr;
    if (head->left != nullptr){
        if (head->left->value == value){
            last = head->left;
        }
    }
    if (head->right != nullptr){
        if (head->right->value == value){
            last = head->right;
        }
    }
    //add to nodesPassed
    if (last != nullptr){ //we are looking at last inserted node
        nodesPassed.push_back(last);
    }
    nodesPassed.push_back(head);

    return head; //returns root bc stack goes down to first
}

//ROTATE
BnRTree::TreeNode *BnRTree::rotate(BnRTree::TreeNode *head) {
    //Case 0: if parent black, just return the red node
    if ((head->parent->red == false) || head->parent->parent == nullptr || head->red == false){
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
        //cout << "uncle Red (change color)" << endl;
        TreeNode* grandfather = head->parent->parent;
        //grandfather turn red and the 2 children turn black
        grandfather->red = true;
        grandfather->right->red = false;
        grandfather->left->red = false;
        return head;
    }
    //Case 2: if uncle black
    else{
        //cout << "uncle Black (rotate later)" << endl;
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
    if (child->right != nullptr){
        child->right->parent = head;
    }
    //child point head right and grandchild left
    child -> right = head;

    return child; //the new head
}

BnRTree::TreeNode *BnRTree::rotateLeft(BnRTree::TreeNode *head) {
    //right child, then right grandchild
    TreeNode* child = head->right;
    TreeNode* grandchild = child->right;

    //head point child's left
    head->right = child -> left;
    if (child->left != nullptr){
        child->left->parent = head;
    }
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
