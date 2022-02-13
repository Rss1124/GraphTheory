#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

typedef struct IPQ{
    int val;
    int pm;
    int im;
};

void init(int length,IPQ array[]);
bool swap(int root,int left,int right,IPQ array[],int length);

int main(){
    IPQ array[15];
    int length=0;
    for(int i=0;i<15;i++){
        int val;
        cout<<"输入一个数字:";
        cin>>val;
        if(val==-1) break;
        else{
            length++;
            array[i].val=val;
        }
    }
    init(length,array);
    for(int i=0;i<length;i++){
        cout<<i<<"-"<<array[i].val<<endl;
    }
}

void init(int length,IPQ array[]){
    bool isSwap=true;
    while(isSwap==true){
        for(int i=(length/2)-1;i>=0;i--){
            isSwap=swap(i,i*2+1,i*2+2,array,length);
        }
    }
}

bool swap(int root,int left,int right,IPQ array[],int length){
    if(right>=length){
        if(array[left].val<array[root].val){ //如果左孩子比根节点小，那么两者进行交换，否则不做处理
            int temp=array[root].val;
            array[root].val=array[left].val;
            array[left].val=temp;
            return true;
        }
    }
    else if(array[left].val<array[right].val){ //如果左孩子比右孩子小，那么根节点继续和左孩子比
        if(array[left].val<array[root].val){ //如果左孩子比根节点小，那么两者进行交换，否则不做处理
            int temp=array[root].val;
            array[root].val=array[left].val;
            array[left].val=temp;
            return true;
        }
    }
    else{ //如果右孩子比左孩子小，那么根节点继续和右孩子比
        if(array[right].val<array[root].val){ //如果右孩子比根节点小，那么两者进行交换，否则不做处理
            int temp=array[root].val;
            array[root].val=array[right].val;
            array[right].val=temp;
            return true;
        }
    }
    return false;
}