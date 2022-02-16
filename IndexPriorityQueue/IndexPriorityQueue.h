#include <iostream>
using namespace std;

typedef struct Heap{
    int val;
    int ki;
};
typedef struct IndexPriorityQueue{
    int val=-1;
    int pm=-1;
    int im=-1;
}IPQ;

void initMinHeap(int length,Heap array[]); //初始化小顶堆
void push(int &length,int value,IPQ queue[]); //索引优先队列入队操作
void pop(int &length,int ki,IPQ queue[]); //索引优先队列出队操作
void update(int ki,int value,IPQ queue[],int length); //更新队列的元素
void swim(int length,IPQ queue[]); //在堆中插入数据后的上浮操作
void sink(int root,IPQ queue[],int length); //在堆中删除数据后的下沉操作
bool smaller(int i,int j,IPQ queue[]); //比较大小
void swap(int i,int j,IPQ queue[]); //交换queue中的元素
void decreaseKey(int ki,int value,IPQ queue[]); //如果更新的元素比原来的小,则执行上浮操作
void increaseKey(int ki,int value,IPQ queue[],int length); //如果更新的元素比原来的大，则执行下沉操作