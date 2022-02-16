#ifndef CUCKOO_H
#define CUCKOO_H
#include<iostream>
using namespace std;

struct Node{
    int key;
    int value;
    Node(int k=-1,int val=0):key(k),value(val){}
    ~Node(){}
};

class CuckooHashing{
private:
    Node* table0;
    Node* table1;
    int size;
    void resize(Node *t);
    int H1(int key) {return key%size;}
    int H2(int key) {return (key/size)%size;}
    Node* Kick(Node *t,int &cnt);
public:
    CuckooHashing(int sz=8){
        size=sz;
        table0=new Node[size];
        table1=new Node[size];
    }
    ~CuckooHashing(){}
    void insert(int k,int val);
    void Lookup(int key);
    void Delete(int key);
    void print()const;
};

#endif // CUCKOO_H
