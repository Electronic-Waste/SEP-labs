#include "cuckoo.h"
void CuckooHashing::resize(Node *t){
    Node *oldTable0=table0;
    Node *oldTable1=table1;
    size *=2;
    table0 = new Node[size];
    table1 = new Node[size];
    for (int i=0;i<size/2;++i)
        insert(oldTable0[i].key,oldTable0[i].value);
    for (int i=0;i<size/2;++i)
        insert(oldTable1[i].key,oldTable1[i].value);
    insert(t->key,t->value);
    delete []oldTable0;
    delete []oldTable1;
}

void CuckooHashing::Lookup(int key){
    bool flag1= key==table0[H1(key)].key;
    bool flag2= key==table1[H2(key)].key;
    if (!flag1 && !flag2)
        cout <<"Key Not Found"<<endl;
    else if (flag1)
        cout <<table0[H1(key)].value<<endl;
    else if (flag2)
        cout <<table1[H2(key)].value<<endl;
}

void CuckooHashing::Delete(int key){
    bool flag1= key==table0[H1(key)].key;
    bool flag2= key==table1[H2(key)].key;
    if (!flag1 && !flag2)
        cout <<"Key Not Found"<<endl;
    else if (flag1)
        table0[H1(key)].key=-1;
    else if (flag2)
        table1[H2(key)].key=-1;
}

void CuckooHashing::insert(int k, int val){
   if (k==-1) return;
   Node *t=new Node(k,val);
   int h1=H1(t->key);
   int h2=H2(t->key);
   if (table0[h1].key==-1||table0[h1].key==t->key)
       table0[h1]=*t;
   else if (table1[h2].key==-1||table1[h2].key==t->key)
       table1[h2]=*t;
   else {
       int cnt=0;
       while (cnt<2*size){
           Node* tmp;
           tmp=Kick(t,cnt);
           ++cnt;
           if (tmp==NULL) break;
           else {
              Node *tm=t;
              t=Kick(tmp,cnt);
              delete tm;
              ++cnt;
              if (t==NULL) return;
           }
       }
       if (cnt==2*size){
           cout <<"Loop Detect"<<endl;
           resize(t);
       }
   }
   delete t;
}

Node* CuckooHashing::Kick(Node *t,int &cnt){
    Node *table=(cnt%2==0)?table0:table1;
    int h=(cnt%2==0)?H1(t->key):H2(t->key);
    if (table[h].key==-1){
        table[h]=*t;
        return NULL;
    }
    else {
        Node tmp=table[h];
        table[h]=*t;
        cout <<"Kick "<<tmp.key<<" with "<<t->key<<" in table "<<cnt%2<<' '<<h<<endl;
        return new Node(tmp.key,tmp.value);
    }
}

void CuckooHashing::print() const{
    cout <<"Table0:"<<endl;
    for (int i=0;i<size;++i)
        cout <<"Index:"<<i<<' '<<"Key:"<<table0[i].key<<' '<<"Value:"<<table0[i].value<<endl;
    cout <<"Table1:"<<endl;
    for (int i=0;i<size;++i)
        cout <<"Index:"<<i<<' '<<"Key:"<<table1[i].key<<' '<<"Value:"<<table1[i].value<<endl;
}

