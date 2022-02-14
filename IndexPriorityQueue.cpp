#include <iostream>
using namespace std;

typedef struct Heap{
    int val;
    int ki;
};
typedef struct IndexPriorityQueue{
    int val;
    int pm;
    int im;
}IPQ;

void initMinHeap(int length,Heap array[]); //��ʼ��С����
void insert(int &length,int value,IPQ queue[]); //���������ȶ������Ԫ��
void swim(int length,IPQ queue[]); //�ڶ��в������ݺ���ϸ�����
bool smaller(int root,int child,IPQ queue[]); //�Ƚϴ�С
void swap(int root,int child,IPQ queue[]); //����queue�е�Ԫ��

int main(){
    Heap minHeap[15];
    IPQ queue[15];
    int length=0;
    for(int i=0;i<15;i++){
        int val;
        cout<<"����һ������:";
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
     * �������ȶ�����ϸͼ��������ʾ��
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
     * ��Ӧ��ϵ����:
     * pm: ���е��ѵ�ӳ��
     * im: �ѵ����е�ӳ��
     *
     * ����:
     * �ҵ�queue[5]��С����minHeap���ڵ�λ��: ki=5--->val=9--->pm=11
     * �ҵ�minHeap[5]���������ȶ���queue���ڵ�λ��: pm=5--->val=4--->ki=11--->im=11
     */
     cout<<"ki-val-pm-im"<<endl;
    for(int i=0;i<length;i++){
        cout<<i<<"-"<<queue[i].val<<"-"<<queue[i].pm<<"-"<<queue[i].im<<endl;
    }
    cout<<endl;
    insert(length,2,queue);
    for(int i=0;i<length;i++){
        cout<<i<<"-"<<queue[i].val<<"-"<<queue[i].pm<<"-"<<queue[i].im<<endl;
    }
}

void  initMinHeap(int length,Heap array[]){
    bool isSwap=true;
    while(isSwap==true){
        isSwap=false;
        for(int i=(length/2)-1;i>=0;i--){
            int root=i;
            int left=i*2+1;
            int right=i*2+2;
            if(right>=length){
                if(array[left].val<array[root].val){ //������ӱȸ��ڵ�С����ô���߽��н���������������
                    int tempValue=array[root].val;
                    array[root].val=array[left].val;
                    array[left].val=tempValue;
                    int tempKi=array[root].ki;
                    array[root].ki=array[left].ki;
                    array[left].ki=tempKi;
                    isSwap=true;
                }
            }
            else if(array[left].val<array[right].val){ //������ӱ��Һ���С����ô���ڵ���������ӱ�
                if(array[left].val<array[root].val){ //������ӱȸ��ڵ�С����ô���߽��н���������������
                    int tempValue=array[root].val;
                    array[root].val=array[left].val;
                    array[left].val=tempValue;
                    int tempKi=array[root].ki;
                    array[root].ki=array[left].ki;
                    array[left].ki=tempKi;
                    isSwap=true;
                }
            }
            else{ //����Һ��ӱ�����С����ô���ڵ�������Һ��ӱ�
                if(array[right].val<array[root].val){ //����Һ��ӱȸ��ڵ�С����ô���߽��н���������������
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

void insert(int &length,int value,IPQ queue[]){
    queue[length].val=value;
    queue[length].pm=length;
    queue[length].im=length;
    swim(length,queue);
    length++;
}

void swim(int length,IPQ queue[]){
    for(int i=(length-1)/2;i>0&&smaller(i,length,queue)==true; ){
        swap(i,length,queue);
        length=i;
        i=(length-1)/2;
    }
}

bool smaller(int root,int child,IPQ queue[]){
    if(queue[child].val<queue[root].val) return true;
    else return false;
}

void swap(int root,int child,IPQ queue[]){
    queue[queue[child].im].pm=root;
    queue[queue[root].im].pm=child;
    int tmp=queue[root].im;
    queue[root].im=queue[child].im;
    queue[child].im=tmp;
}