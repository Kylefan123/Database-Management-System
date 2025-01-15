//Kyle Theodore
//May 11 2024 - July 10 2024
//Header File(3 of 3)
//AVL Tree Program

#ifndef AVL_DATABASE_HPP
#define AVL_DATABASE_HPP

#include <string>
#include <vector>
#include <queue>

class Record {
public:
    std::string key;
    int value;

    Record(const std::string& k, int v);
};

class AVLNode {
public:
    Record* record;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Record* r);
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node);
    int balance(AVLNode* node);    
    
    //added
    void updateheight(AVLNode* node);
    
    AVLNode* rotateRight(AVLNode* y);
    AVLNode* rotateLeft(AVLNode* x);
    
    


public:
    AVLTree();
    void insert(Record* record);
    Record* search(const std::string& key, int value);   
    void deleteNode(const std::string& key, int value);

    //added
    AVLNode* getroot();
    void setRoot(AVLNode* node);
    void updateheightAll(AVLNode* node);
    AVLNode* balanceTree(AVLNode* node);
    
    
    

};

class IndexedDatabase {
private:
    AVLTree index;

    //Added
    void rangeQueryR(AVLNode* node, std::vector<Record*>& list, int start, int end);
    void InorderTraversalR(AVLNode* node, std::vector<Record*>& list);
    void clearDatabaseR(AVLNode* node);
    int count(AVLNode* node);


public:
    void insert(Record* record);
    Record* search(const std::string& key, int value);
    void deleteRecord(const std::string& key, int value);
    std::vector<Record*> rangeQuery(int start, int end);
    std::vector<Record*> findKNearestKeys(int key, int k);
    std::vector<Record*> inorderTraversal();    
    
    
    void clearDatabase();
    int countRecords();
};

#endif // AVL_DATABASE_HPP
