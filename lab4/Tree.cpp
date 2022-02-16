#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <limits.h>
#include <vector>
#include <queue>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
int TreeNode::getX(){
    return data[0];
}

int TreeNode::getY(){
    return data[1];
}

TreeNode::TreeNode(int x,int y,TreeNode *l,TreeNode *r){
    data[0]=x;data[1]=y;left=l;right=r;
}

TreeNode::~TreeNode(){
    if (!left) delete left;
    if (!right) delete right;
}

long long int distance(TreeNode *t1, TreeNode *t2){
    long long int x1=t1->getX(),x2=t2->getX();
    long long int y1=t1->getY(),y2=t2->getY();
    return (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
}

BinaryDimonTree::BinaryDimonTree(){
    root=NULL;
}

BinaryDimonTree::~BinaryDimonTree(){
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty()){
        if (que.front()->left !=NULL)
            que.push(que.front()->left);
        if (que.front()->right !=NULL)
            que.push(que.front()->right);
        TreeNode *tmp=que.front();
        que.pop();
        delete tmp;
    }
}

void BinaryDimonTree::Pos_Search(TreeNode *cur,TreeNode *t){
    if (!t) return;
    if (t->left==NULL && cur->data[t->boldNum]<t->data[t->boldNum]) {
        t->left = cur;
        cur->setBoldNum((t->boldNum+1)%2);
        return;
    }
    else if(t->right==NULL && cur->data[t->boldNum]>=t->data[t->boldNum]) {
        t->right = cur;
        cur->setBoldNum((t->boldNum+1)%2);
        return;
    }
    else {
        if(cur->data[t->boldNum]<t->data[t->boldNum])
            Pos_Search(cur,t->left);
        else
            Pos_Search(cur,t->right);
    }
}

istream &operator>>(istream &in, BinaryDimonTree &tree){
    int numOfnode;
    in >> numOfnode;
    int tmp=numOfnode;
    queue<TreeNode*> que;
    while (tmp-- >0) {
        int xvalue,yvalue;
        in >> xvalue >> yvalue;
        if (!tree.root) {
           tree.root=new TreeNode(xvalue,yvalue);
           tree.root->setBoldNum(0);
        }
        else {
           TreeNode* current=new TreeNode(xvalue,yvalue);
           tree.Pos_Search(current,tree.root);
        }
    }
}

TreeNode* BinaryDimonTree::find_nearest_node(int x, int y){
    TreeNode *test_point=new TreeNode(x,y);
    TreeNode *guess=NULL;
    long long int bestDist;
    bestDist=INT_MAX;

    TreeNode* curr=root;
    recur_search(curr,test_point,bestDist,guess);
    return guess;
}

void BinaryDimonTree::recur_search(TreeNode *cur,TreeNode *test, long long int &min_distance, TreeNode*& guess){
    if (cur == NULL) return;
    if (distance(cur,test) <min_distance) {
        min_distance=distance(cur,test);
        guess=cur;
    }
    else if(distance(cur,test)==min_distance) {
        if (cur->getX()<guess->getX()
                || cur->getX()==guess->getX()&&cur->getY()<guess->getY()) guess=cur ;
    }
    if (test->data[cur->boldNum]<cur->data[cur->boldNum])
        recur_search(cur->left,test,min_distance,guess);
    else recur_search(cur->right,test,min_distance,guess);

    if (abs(cur->data[cur->boldNum]-test->data[cur->boldNum])<min_distance) {
        if (test->data[cur->boldNum]<cur->data[cur->boldNum])
            recur_search(cur->right,test,min_distance,guess);
        else recur_search(cur->left,test,min_distance,guess);
    }

}




