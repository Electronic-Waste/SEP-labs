#include <iostream>
#include "cuckoo.h"
#include <string>
using namespace std;

int main()
{
   int M;
   cin >>M;
   int key,val;
   CuckooHashing cuckoo;
   while (M-- >0){
       string cmd;
       cin >>cmd;
       if (cmd=="Insert"){
           cin>>key>>val;
           cuckoo.insert(key,val);
//           cuckoo.print();
       }
       else if (cmd=="Lookup"){
           cin >>key;
           cuckoo.Lookup(key);
       }
       else if (cmd=="Delete"){
           cin >>key;
           cuckoo.Delete(key);
       }
   }
   return 0;
}
