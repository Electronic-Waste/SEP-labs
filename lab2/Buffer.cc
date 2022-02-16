#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer


Buffer::Buffer() {
   head = new list;
   maxSize = 0;
   currentLineNum = 0;
}

Buffer::~Buffer() {
   deleteLines(1,maxSize);
   delete head;
}

void Buffer::writeToFile(const string &filename) const {
    fstream input(filename);
    list *p = head;
    int byte=0;

    while (p->next) {
        p = p->next;
        byte += p->line.size()+1;
        input << p->line<<'\n';
    }

    input.close();
    cout <<byte<<" byte(s) written"<<endl;
}

void Buffer::showLines(int from, int to) {
    if (from > to)
        throw "Number range error";
    if ( from <=0 || to >maxSize)
        throw "Line number out of range";
    else for (int i=from; i<=to; ++i)
        cout <<moveToLine(i)<<endl;

}

void Buffer::deleteLines(int from, int to){
    if (from > to)
        throw "Delete range error";
    if ( from <=0 || to >maxSize)
        throw "Line number out of range";
    else for (int i=from; i<=to; ++i) {
        list* node= MOVE(from-1);

        if (node->next) {
            list* p= node->next;
            node->next = MOVE(from+1);
            delete p;
            if (currentLineNum == 1) currentLineNum =0;
            else currentLineNum = from;
            --maxSize;
        }

        else {
            delete node->next;
            MOVE(from-1)->next = NULL;
            --maxSize;
            currentLineNum = from-1;
            cout <<"currentLineNum is:"<<currentLineNum<<endl;
        }
    }
}

void Buffer::insertLine(const string &text){
    if (currentLineNum == 0) {
        list* node = new list(text);
        head->next = node;
    }

    list* node = new list(text,MOVE(currentLineNum));
    MOVE(currentLineNum-1)->next = node;
    ++maxSize;
}

void Buffer::appendLine(const string &text){
    list* node = new list(text,MOVE(currentLineNum+1));
    MOVE(currentLineNum)->next = node;
    ++maxSize;
    ++currentLineNum;
}

const string &Buffer::moveToLine(int idx) {
    cout <<idx<<'\t';
    currentLineNum = idx;
    return MOVE(idx)->line;
}

