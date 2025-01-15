//Kyle Theodore
//May 11 2024 - July 10 2024
//Declaration File(2 of 3)
//AVL Tree Program

#include "AVL_Database.hpp"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;


Record::Record(const std::string& k, int v) : key(k), value(v) {}

AVLNode::AVLNode(Record* r) : record(r), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr) {}

int AVLTree::height(AVLNode* node) {        //returns node height return 0 for and left and right nodes of leaves
    return node ? node->height : 0;
}

int AVLTree::balance(AVLNode* node) {       //[-1,1] if diffrence is not in range not balanced
    return node ? height(node->left) - height(node->right) : 0;
    // if nullptr node is false; condtion ? True : False
}

//added
void AVLTree::updateheight(AVLNode* node) {
    //varables    
    int lefthight = 0, righthight = 0;

    //find hight of left node
    if (node->left) { lefthight = node->left->height; }
    //find hight of right node
    if (node->right) { righthight = node->right->height; }
    
    //right and left node:     greater of the 2;
    if (lefthight > righthight) { node->height = lefthight + 1; }
    else { node->height = righthight + 1; }
}

AVLNode* AVLTree::rotateRight(AVLNode* y) {  
    
    //saved varables   
    AVLNode* L1 = y->left;          //y->left(L1)
    AVLNode* LR1 = y->left->right;  //y->left->right(LR1)
       
    L1->right = y;                  //node(y) becomes right child of left(L1) child.
    y->left = LR1;                  //saved node right->left(RL1) becomes left child of node(y).
      
    this->updateheight(y);          //update hight of node(y)   
    this->updateheight(L1);         //updata hight of node left(L1)
     
    
    return L1;                      //return node left.      

    return nullptr;


}

AVLNode* AVLTree::rotateLeft(AVLNode* x) {    
    
    //Saved Varables
    AVLNode* R1 = x->right;         //save node x->right(R1)
    AVLNode* RL1 = x->right->left;  //save node x->right->left(RL1)
        
    R1->left = x;                   //node(x) becomes left child of right(R1) child    
    x->right = RL1;                 //saved node(x) right->left(RL1) becomes right child of node(x).

    this->updateheight(x);          //update height of node(x)   
    this->updateheight(R1);         //updata height of node right(R1)
    
    return R1;                      //return node right(R1)

    return nullptr;

}

void AVLTree::insert(Record* record) { // insert a new record with the given key value pair 

    //add new new node:
    AVLNode* NewNode = new AVLNode(record);
      
    //if tree is empty add set new node as root and end
    if (root == nullptr) { root = NewNode; }                
    
    //Create Variables
    AVLNode* tempNode = nullptr;
    AVLNode* current = nullptr;
    AVLNode* preNode = nullptr;
    bool preDiction = false;

    AVLNode* preUBNode = nullptr;
    AVLNode* UBNode = nullptr;
    bool UBDiection = false;
    bool first = false;
    bool second = false;
    bool flag = false;

    preNode = root;
    current = root;
    
    //loop (current != nullptr)
    while (current->record != NewNode->record) {
        
        // new node > current go right
        if (NewNode->record->value > current->record->value) {
            
            if (current->right == nullptr) {
                
                current->right = NewNode;        //add node 
                this->updateheight(current);     //update hight of current node.
            }
            //curent->right has node
            else {

                current->right->height += 1;             //current->right height +1
                this->updateheight(current);            //update current height
                
            }

            //unblanced != nullptr and Flag = false
            if (UBNode != nullptr && flag == false) {                
                second = true;                  //second = right
                flag = true;                    //flag = true
            }
            //current node is unbanced
            if ((this->balance(current) < -1 || 1 < this->balance(current)) && !flag) {
               
                preUBNode = preNode;            //preUBNode = preNode
                UBNode = current;               //UBNode = current node
                UBDiection = preDiction;        //UBDerection = preDerection
                first = true;                   //fist = right
                
            }

            preNode = current;                  //preNode = current
            preDiction = true;                  //preDerection = right;
            current = current->right;           //current = current->right
        }
        
        // new node < current go left
        else {
            
            //current->left is null
            if (current->left == nullptr) {
                current->left = NewNode;        //add node 
                this->updateheight(current);    //update hight of current node.
            }
            //curent->left has node
            else {
                current->left->height += 1;     //current->left height +1
                this->updateheight(current);    //update current height
                
            }

            //unblanced != nullptr and Flag = false
            if (UBNode != nullptr && flag == false) {
                second = false;                  //second = left
                flag = true;                    //flag = true
            }

            //current node is unbanced
            if ( (this->balance(current) < -1 || 1 < this->balance(current)) && !flag) {
                if(current->left)
                preUBNode = preNode;            //preUBNode = preNode
                UBNode = current;               //UBNode = current node
                UBDiection = preDiction;        //UBDerection = preDerection
                first = false;                  //fist = left
               
            }

            preNode = current;                  //preNode = current
            preDiction = false;                 //preDerection = left
            current = current->left;            //current = current->left

        }

        

    }
    //end loop

    //if UBNode node !=nullptr
    if (UBNode != nullptr) {       

        //left left
        if (!first && !second) {

            tempNode = this->rotateRight(UBNode);                     //Rotate Right(unblanced node)

        }
        //left right
        else if (!first && second) {
           
            UBNode->left = this->rotateLeft(UBNode->left);          //Rotate left(unblalanced node->left)
            tempNode = this->rotateRight(UBNode);                     //Rotate right(unbalanced node)

        }
        //right right
        else if (first && second) {
            
            tempNode = this->rotateLeft(UBNode);                      //Rotate left(unblanced node)

        }
        //right left
        else {
            
            UBNode->right = this->rotateRight(UBNode->right);       //Rotate right(unblanced node->right)
            tempNode = this->rotateLeft(UBNode);                    //Rotate left(unblanced node)

        }
        
        if (UBNode == root) { 
            root = tempNode;
            this->updateheight(root);
            
        }
        else {
            if (UBDiection == false) { 
                preUBNode->left = tempNode; 
                
            }
            else {preUBNode->right = tempNode;
            
            }
            this->updateheight(preUBNode);
        }
        this->updateheightAll(root);
        this->balanceTree(root);
       
    }

}

Record* AVLTree::search(const std::string& key, int value) {    
    

    AVLNode* current = root;    
    
    while (current != nullptr) {
     
        // current value > search value, go left on tree
        if(current->record->value  > value){
            
            current = current->left;
            continue;            
        }
        // current value < search value, go right on tree
        if (current->record->value < value){
            
            current = current->right;
            continue;
        }
        // current value = search value and current key = search key, return current record.
        if (current->record->value == value){           
            
            if(current->record->key == key){return current->record;}
            current = nullptr;
                  
        }

    }

    Record* temp = new Record("", 0);
    return temp;
        
    
}

void AVLTree::deleteNode(const std::string& key, int value) {

    
    AVLNode* preNode = root;
    bool preDirection = false;
    AVLNode* current = root;
    AVLNode* targetNode = nullptr;

    //search for node
    while (current != nullptr) {

        
        // current value > search value, go left on tree
        if (current->record->value > value) {
            
            preDirection = false;           //left
            preNode = current;
            current = current->left;
            continue;
        }
        // current value < search value, go right on tree
        if (current->record->value < value) {
            
            preDirection = true;            //right
            preNode = current;
            current = current->right;
            continue;
        }
        // current value = search value and current key = search key, return current record.
        if (current->record->value == value) {

            if (current->record->key == key) { targetNode = current ; }            
            current = nullptr;

        }
        

    }
      

    if (targetNode == nullptr) { return; }
    

    //for leaf node Deleat node
    if (targetNode->left == nullptr && targetNode->right == nullptr) {
                
        if (preDirection == false) { preNode->left = nullptr; }
        else { preNode->right = nullptr; }
        delete targetNode->record;
        delete targetNode;

    }
    //for node with 1 child replace node with child
    else if (targetNode->left == nullptr && targetNode->right != nullptr) {
        
        if (preDirection == false) { preNode->left = targetNode->right; }
        else { preNode->right = targetNode->right; }
        delete targetNode->record;
        delete targetNode;
    }
    else if (targetNode->left != nullptr && targetNode->right == nullptr) {
        
        if (preDirection == false) { preNode->left = targetNode->left; }
        else { preNode->right = targetNode->left; }
        delete targetNode->record;
        delete targetNode;
    }
    //for node with 2 child
    else if(targetNode->left != nullptr && targetNode->right != nullptr) {

        
        //replace node with largest node of left subtree
        //find largest node        
        
        AVLNode* largestNode = targetNode->left;
        AVLNode* preLargestNode = targetNode;
        current = targetNode->left;

        while (current != nullptr) {          
            
            if (current->right == nullptr) {                
                largestNode = current;
                break;            
            }
            preLargestNode = current;
            current = current->right;
        }

        //[leaf node]
        if (largestNode->left == nullptr && largestNode->right == nullptr) {
            if (preDirection == false) { preNode->left = largestNode; }
            else { preNode->right = largestNode; }
            preLargestNode->right = nullptr;
            largestNode->left = targetNode->left;
            largestNode->right = targetNode->right;
            delete targetNode->record;
            delete targetNode;
        }
        //[No Right node]
        else {
            // go left until leaf node
            AVLNode* leftmostNode = nullptr;
            current = largestNode;
            while (current != nullptr) {

                if (current->left == nullptr) { 
                    leftmostNode = current;
                }
                current = current->left;

            }
            
            
            if (preDirection == false) { preNode->left = largestNode; }
            else { preNode->right = largestNode; }
            
            //make hanging pointer nullptr
            if (targetNode == preLargestNode) {
                targetNode->left = nullptr;
            }
            else {
                preLargestNode->right = nullptr;
            }
            
            largestNode->right = targetNode->right;
            leftmostNode->left = targetNode->left;
            delete targetNode->record;
            delete targetNode;



        }
            


    }
              
    
        //reblance tree.
        root = balanceTree(root);


}

//added
AVLNode* AVLTree::getroot() {return root;}
void AVLTree :: setRoot(AVLNode* node) {root = node;}
void AVLTree::updateheightAll(AVLNode* node) {

    if (node == nullptr) { return; }

    this->updateheightAll(node->left);
    this->updateheightAll(node->right);
    
    this->updateheight(node);
    

}
AVLNode* AVLTree :: balanceTree(AVLNode* node){
    
    if (node == nullptr) { return nullptr; }
    AVLNode* leftNode = nullptr;
    AVLNode* rightNode = nullptr;
    
    leftNode = this->balanceTree(node->left);
    updateheightAll(leftNode);
    rightNode = this->balanceTree(node->right);
    updateheightAll(rightNode);    
    node->left  = leftNode;
    node->right = rightNode;    
    updateheight(node);
    if (this->balance(node) > 1 || -1 > this->balance(node)) {
        
        if (node->left == nullptr) { node = rotateLeft(node); }
        else if (node->right == nullptr) { node = rotateRight(node); }
        else if (node->left->height < node->right->height) { node = rotateLeft(node); }
        else { node = rotateRight(node); }

    }

    return node;
    
}

void IndexedDatabase::insert(Record* record) { index.insert(record);}
Record* IndexedDatabase::search(const std::string& key, int value) { return index.search(key, value); }

void IndexedDatabase::deleteRecord(const std::string& key, int value) {

    //call delete node
    index.deleteNode(key, value);


}

std::vector<Record*> IndexedDatabase::rangeQuery(int start, int end) {
    
    std::vector<Record*> rvector;
    AVLNode* root = index.getroot();    
    this->rangeQueryR(root, rvector, start, end);
    return rvector;
}

std::vector<Record*> IndexedDatabase::findKNearestKeys(int key, int k) {    
    
    std::vector<Record*> allRecords = this->inorderTraversal();
    
    auto compare = [key](Record* a, Record* b) {
        return std::abs(a->value - key) < std::abs(b->value - key);
    };
    std::priority_queue<Record*, std::vector<Record*>, decltype(compare)> pq(compare);      
    
    for (Record* record : allRecords) {
        pq.push(record);
        if (pq.size() > k) {
            pq.pop();
        }
    }
    std::vector<Record*> result;
    while (!pq.empty()) {
        result.push_back(pq.top());
        pq.pop();
    }
    //std::reverse(result.begin(), result.end());
    return result;
    
}

void IndexedDatabase::rangeQueryR(AVLNode* node, std::vector<Record*>& list , int start , int end) {
    
    //RecursiveFuntionFor INorderTraversal
       //left->root->right
    if (node == nullptr) { return; }

    this->rangeQueryR(node->left, list, start, end);
    
    if (node->record->value >= start && end >= node->record->value) { 
        
        list.push_back(node->record);         

    }  

    this->rangeQueryR(node->right, list, start, end);

}

std::vector<Record*> IndexedDatabase::inorderTraversal() {
    //left->root->right
    //create varbles
    std::vector<Record*> rvector;
    AVLNode* current = index.getroot();
    
    //call Recursive Function and Return  vectorlist of records
    this->InorderTraversalR(current, rvector);    
    return rvector;
}
//added
void IndexedDatabase :: InorderTraversalR(AVLNode* node, std::vector<Record*>& list) {
    
    //RecursiveFuntionFor INorderTraversal
        //left->root->right
    if (node == nullptr) { return;}

    this->InorderTraversalR(node->left, list);
    
    list.push_back(node->record);
    

    this->InorderTraversalR(node->right, list);
        
}

void IndexedDatabase :: clearDatabaseR(AVLNode * node) {
    
    //RecursiveFuntionFor clearingDatabase
        //left->root->right
    if (node == nullptr) { return; }

    this->clearDatabaseR(node->left);

    this->clearDatabaseR(node->right);

    delete node->record;
    delete node;



}

int IndexedDatabase::count(AVLNode* node) {
    
    //RecursiveFuntionFor INorderTraversal
    int sum = 0;
        //left->root->right
    if (node == nullptr) { return 0; }

    sum += this->count(node->left);
    
    
    sum += this->count(node->right);

    return sum + 1;
}

void IndexedDatabase::clearDatabase() {
   
    AVLNode* root = index.getroot();

    clearDatabaseR(root);

    index.setRoot(nullptr);


}

int IndexedDatabase::countRecords() {    
    
    AVLNode* root = index.getroot();
    return count(root);
}

