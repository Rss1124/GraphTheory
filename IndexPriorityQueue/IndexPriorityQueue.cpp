#include <iostream>
#include "IndexPriorityQueue.h"
using namespace std;

void initMinHeap(int length,Heap array[]){
    bool isSwap=true;
    while(isSwap==true){
        isSwap=false;
        for(int i=(length/2)-1;i>=0;i--){
            int root=i;
            int left=i*2+1;
            int right=i*2+2;
            if(right>=length){
                if(array[left].val<array[root].val){ //如果左孩子比根节点小，那么两者进行交换，否则不做处理
                    int tempValue=array[root].val;
                    array[root].val=array[left].val;
                    array[left].val=tempValue;
                    int tempKi=array[root].ki;
                    array[root].ki=array[left].ki;
                    array[left].ki=tempKi;
                    isSwap=true;
                }
            }
            else if(array[left].val<array[right].val){ //如果左孩子比右孩子小，那么根节点继续和左孩子比
                if(array[left].val<array[root].val){ //如果左孩子比根节点小，那么两者进行交换，否则不做处理
                    int tempValue=array[root].val;
                    array[root].val=array[left].val;
                    array[left].val=tempValue;
                    int tempKi=array[root].ki;
                    array[root].ki=array[left].ki;
                    array[left].ki=tempKi;
                    isSwap=true;
                }
            }
            else{ //如果右孩子比左孩子小，那么根节点继续和右孩子比
                if(array[right].val<array[root].val){ //如果右孩子比根节点小，那么两者进行交换，否则不做处理
                    int tempValue=array[root].val;
                    array[root].val=array[right].val;
                    array[right].val=tempValue;
                    int tempKi=array[root].ki;
                    array[root].ki=array[right].ki;
                    array[right].ki=tempKi;
                    isSwap=true;
                }
            }
        }
    }
}

void push(int &length,int value,IPQ queue[]){
    queue[length].val=value;
    queue[length].pm=length;
    queue[length].im=length;
    swim(length,queue);
    length++;
}

void pop(int &length,int ki,IPQ queue[]){
    int i=queue[ki].pm;
    swap(i,length-1,queue);
    length--;
    sink(i,queue,length); //i=0,length=12
    queue[ki].val=-1;
    queue[ki].pm=-1;
    queue[length].im=-1;
}

void swim(int length,IPQ queue[]){
    for(int i=(length-1)/2;length>0&&smaller(length,i,queue)==true; ){
        swap(i,length,queue);
        length=i;
        i=(length-1)/2;
    }
}

void sink(int root,IPQ queue[],int length){ //i=0,length=12
    while(true){
        int left=2*root+1;
        int right=2*root+2;
        int smallest=left;
        if(right<length&&smaller(right,left,queue)==true) smallest=right;
        if(left>=length||smaller(root,smallest,queue)==true) break;
        swap(smallest,root,queue);
        root=smallest;
    }
}

bool smaller(int i,int j,IPQ queue[]){
    if(queue[queue[i].im].val<queue[queue[j].im].val) return true; //注意这里要通过heap到queue的映射im来比较大小
    else return false;
}

void swap(int i,int j,IPQ queue[]){
    queue[queue[j].im].pm=i;
    queue[queue[i].im].pm=j;
    int tmp=queue[i].im;
    queue[i].im=queue[j].im;
    queue[j].im=tmp;
}

void update(int ki,int value,IPQ queue[],int length){
    int i=queue[ki].pm; //i=6
    queue[ki].val=value;
    sink(i,queue,length);
    swim(i,queue);
}

void decreaseKey(int ki,int value,IPQ queue[]){
    if(smaller(value,queue[ki].val,queue)){
        queue[ki].val=value;
        swim(queue[ki].pm,queue);
    }
}

void increaseKey(int ki,int value,IPQ queue[],int length){
    if(smaller(queue[ki].val,value,queue)){
        queue[ki].val=value;
        sink(queue[ki].pm,queue,length);
    }
}
