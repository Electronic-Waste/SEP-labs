#pragma once

#include <string>
using namespace std;
using std::string;

class Buffer {

    private:
    int maxSize;
    int currentLineNum;
    // TODO: add a List here for storing the input lines    
    struct list{
        string line;
        list *next;

        list(const string &str = "", list *Next = NULL):line(str),next(Next){}
        ~list(){}
    };
public:
    Buffer();
    ~Buffer();

    list* head;
    void writeToFile(const string &filename) const;
    const string &moveToLine(int idx);
    int getCurrentLineNum(){return currentLineNum;}
    int getMaxSize(){return maxSize;}
    void showLines(int from, int to);
    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);

    //可能改变内容，移到第idx个节点（行）
    list* MOVE(int idx) {
        list* p=head;
        if (idx >maxSize || idx <0)
            return NULL;
        while (--idx >=0)
            p = p->next;
        return p;
    }
};
