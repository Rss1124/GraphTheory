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

int main(){
    Heap minHeap[15];
    IPQ queue[15];
    int length=0;
    for(int i=0;i<15;i++){
        int val;
        cout<<"输入一个数字:";
        cin>>val;
        if(val==-1) break;
        else{
            length++;
            minHeap[i].val=val;
            minHeap[i].ki=i;
        }
    }
    initMinHeap(length,minHeap);
    for(int pm=0;pm<length;pm++){
        queue[minHeap[pm].ki].val=minHeap[pm].val;
        queue[minHeap[pm].ki].pm=pm;
        queue[pm].im=minHeap[pm].ki;
    }
    /**
     * 索引优先队列详细图解如下所示：
     * pm-val   val-ki
     * 0  1      3  0
     * 1  3     15  1
     * 2  2     11  2
     * 3  6     17  3
     * 4  5      7  4
     * 5  4      9  5
     * 6  11     2  6
     * 7  17     1  7
     * 8  15     6  8
     * 9  7      5  9
     * 10 16     16 10
     * 11 9      4  11
     *
     * 对应关系如下:
     * pm: 队列到堆的映射
     * im: 堆到队列的映射
     *
     * 举例:
     * 找到queue[5]在小顶堆minHeap所在的位置: ki=5--->val=9--->pm=11
     * 找到minHeap[5]在索引优先队列queue所在的位置: pm=5--->val=4--->ki=11--->im=11
     */
    cout<<"ki-val-pm-im"<<endl;
    for(int i=0;i<length;i++) cout<<"("<<i<<")"<<"-"<<"("<<queue[i].val<<")"<<"-"<<"("<<queue[i].pm<<")"<<"-"<<"("<<queue[i].im<<")"<<endl;
    cout<<endl;
    push(length,2,queue);
    for(int i=0;i<length;i++) cout<<"("<<i<<")"<<"-"<<"("<<queue[i].val<<")"<<"-"<<"("<<queue[i].pm<<")"<<"-"<<"("<<queue[i].im<<")"<<endl;
    cout<<endl;
    int index=length;
    pop(length,queue[0].im,queue);
    for(int i=0;i<index;i++) cout<<"("<<i<<")"<<"-"<<"("<<queue[i].val<<")"<<"-"<<"("<<queue[i].pm<<")"<<"-"<<"("<<queue[i].im<<")"<<endl;
    cout<<endl;
    update(2,1,queue,length);
    for(int i=0;i<index;i++) cout<<"("<<i<<")"<<"-"<<"("<<queue[i].val<<")"<<"-"<<"("<<queue[i].pm<<")"<<"-"<<"("<<queue[i].im<<")"<<endl;
}

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
