#include "termio.h"

// Do not delete the following line
char Termio::buffer[Termio::CANVAS_HEIGHT][Termio::CANVAS_WIDTH + 1];

void write_hi() {
    for (int j=0;j<41;++j)
        Termio::buffer[10][j]='-';
    for (int i = 0; i < 11; i++) {
        Termio::buffer[i][5] = '|';
        Termio::buffer[i][20] = '|';
        Termio::buffer[i][35] = '|';
    }

}

class linkStack_H
{
friend void write(linkStack_H &A,linkStack_H &B,linkStack_H &C);
private:
    struct node{
       int size;
       node* next;
       node(int sz,node* N=NULL){
           size=sz;next=N;
       }
       node():next(NULL){}
       ~node(){}
    };
    node* top_p;
    int num;
public:
    int cixu;
    linkStack_H(int c,int n=0){
        top_p=NULL;
        cixu=c;
        num=0;
        int tmp=n;
        while (tmp>0){
            push(tmp);
            --tmp;
        }
    }
    ~linkStack_H(){
        node* tmp=top_p;
        while (top_p) {
            top_p=top_p->next;
            delete tmp;
        }
    }
    int top(){
        return top_p->size;
    }
    int pop(){
        node* tmp=top_p;
        top_p=top_p->next;
        int x=tmp->size;
        delete tmp;
        --num;
        return x;
    }
    void push(int d){
        top_p=new node(d,top_p);
        ++num;
    }
    bool isEmpty(){
        return top_p==NULL;
    }
    void write();
};

class linkStack_P
{
private:
    struct node{
       int former;
       int later;
       node* next;
       node(int f,int l,node* N=NULL){
           former=f;later=l;next=N;
       }
       node():next(NULL){}
       ~node(){}
    };
    node* top_p;
public:
    linkStack_P(){
        top_p=NULL;
    }
    ~linkStack_P(){
        node* tmp=top_p;
        while (top_p) {
            top_p=top_p->next;
            delete tmp;
        }
    }
    void top(int &f,int &l){
        f=top_p->former;l=top_p->later;
    }
    void pop(){
        node* tmp=top_p;
        top_p=top_p->next;
        delete tmp;
    }
    void push(int f,int l){
        top_p=new node(f,l,top_p);
    }
    bool isEmpty(){
        return top_p==NULL;
    }
};

void Auto_move(linkStack_H *A,linkStack_H *B,linkStack_H *C) {
    int tmp=A->pop();
    B->push(tmp);
    Termio::ResetBuffer();
    write_hi();
    A->write();
    B->write();
    C->write();
    cout <<"Auto moving:"<<A->cixu<<"->"<<B->cixu<<endl;
    Termio::Draw();

}

void hanoi(int n,linkStack_H *A,linkStack_H *B,linkStack_H *C) {
    if (n==1) Auto_move(A,B,C);
    else {
        hanoi(n-1,A,C,B);
        Auto_move(A,B,C);
        hanoi(n-1,C,B,A);
    }
}

void hanoi_enhanced(int a,int b,int c,linkStack_H *A,linkStack_H *B,linkStack_H *C) {
    if (b+c>=1) hanoi(b+c,A,B,C);
    if (c>=1) hanoi(c,B,C,A);
}

void linkStack_H::write(){
    if (isEmpty()) return;
    int line=15*cixu-10;
    int cnt=num;
    int arr[num];
    node* p=top_p;
    while (cnt-- >0){
        arr[cnt]=p->size;
        p=p->next;
    }
    for (int i=0;i<num;++i){
        int tmp=arr[i];
        for (int j=-tmp;j<=tmp;++j){
            Termio::buffer[9-2*i][line+j]='*';
        }
    }
}

bool Normal_move(int fo,int la,linkStack_H *A,linkStack_H *B,linkStack_H *C){
    linkStack_H *Fstack,*Lstack;
    switch(fo){
        case 1:Fstack=A;break;
        case 2:Fstack=B;break;
        case 3:Fstack=C;break;
    }
    switch(la){
        case 1:Lstack=A;break;
        case 2:Lstack=B;break;
        case 3:Lstack=C;break;
    }
    if (Fstack->isEmpty()) {
        Termio::Draw();
        return false;
    }
    if (Lstack->isEmpty()||Fstack->top()<Lstack->top()) {
        Lstack->push(Fstack->pop());
        Termio::ResetBuffer();
        write_hi();
        A->write();
        B->write();
        C->write();
        Termio::Draw();
        return true;
    }
    else {
        Termio::Draw();
        return false;
    }

}

int main() {

    // ----------- End of example -----------
    while (true) {
        cout <<"How many disks do you want? (1 ~ 5)"<<endl;
        char numOfstack;
        cin >>numOfstack;
        if (numOfstack=='Q') break;
        else if (numOfstack-'0'<1 || numOfstack-'0'>5) continue;
        else {
            linkStack_H *A,*B,*C;
            A=new linkStack_H(1,numOfstack-'0');
            B=new linkStack_H(2);
            C=new linkStack_H(3);
            linkStack_P *P=new linkStack_P;
            Termio::ResetBuffer();
            write_hi();
            A->write();
            B->write();
            C->write();
            Termio::Draw();
            int n1,n2,n3;
            cout <<"Move a disk. Format: x y"<<endl;
            while (true){
                cin >>n1;
                cin >>n2;
                if (n1>=1&&n1<=3 && n2>=1&&n2<=3) {
                    bool flag=Normal_move(n1,n2,A,B,C);
                    cout <<"Move a disk. Format: x y"<<endl;
                    if (flag) P->push(n1,n2);
                    if (A->isEmpty() && C->isEmpty()) {
                        cout <<"Congratulations! You win!"<<endl;
                        break;
                    }
                    continue;
                }
                else if (n1==0 && n2==0) {
                    while (!P->isEmpty()){
                        int f,l;
                        P->top(l,f);
                        P->pop();
                        cout <<"Auto moving:"<<f<<"->"<<l<<endl;
                        Normal_move(f,l,A,B,C);
                    }
                    hanoi(numOfstack-'0',A,B,C);
                    cout <<"Congratulations! You win!"<<endl;
                    break;
                }
                else if (n1<=0 && n2<=0) {
                    cin >>n3;
                    if (n1+n2+n3 != -(numOfstack-'0')) continue;
                    n1=-n1;n2=-n2;n3=-n3;
                    while (!P->isEmpty()){
                        int f,l;
                        P->top(l,f);
                        P->pop();
                        cout <<"Auto moving:"<<f<<"->"<<l<<endl;
                        Normal_move(f,l,A,B,C);
                    }
                    if (n2!=0 || n3!=0) hanoi_enhanced(n1,n2,n3,A,B,C);
                    else  {
                        Termio::ResetBuffer();
                        write_hi();
                        A->write();
                        Termio::Draw();
                    }
                    cout <<"Congratulations! You win!"<<endl;
                    break;
                }
                else {
                    Termio::ResetBuffer();
                    write_hi();
                    A->write();
                    B->write();
                    C->write();
                    Termio::Draw();
                    cout <<"Move a disk. Format: x y"<<endl;
                    continue;
                }
            }
        }
    }
    // some output hints that you should use.
    //std::cout << "How many disks do you want? (1 ~ 5)" << std::endl;
    //std::cout << "Move a disk. Format: x y" << std::endl;
    //std::cout << "Auto moving:1->2" << std::endl;
    //std::cout << "Congratulations! You win!" << std::endl;

    return 0;
}
