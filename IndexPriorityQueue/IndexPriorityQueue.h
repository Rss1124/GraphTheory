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

void initMinHeap(int length,Heap array[]); //��ʼ��С����
void push(int &length,int value,IPQ queue[]); //�������ȶ�����Ӳ���
void pop(int &length,int ki,IPQ queue[]); //�������ȶ��г��Ӳ���
void update(int ki,int value,IPQ queue[],int length); //���¶��е�Ԫ��
void swim(int length,IPQ queue[]); //�ڶ��в������ݺ���ϸ�����
void sink(int root,IPQ queue[],int length); //�ڶ���ɾ�����ݺ���³�����
bool smaller(int i,int j,IPQ queue[]); //�Ƚϴ�С
void swap(int i,int j,IPQ queue[]); //����queue�е�Ԫ��
void decreaseKey(int ki,int value,IPQ queue[]); //������µ�Ԫ�ر�ԭ����С,��ִ���ϸ�����
void increaseKey(int ki,int value,IPQ queue[],int length); //������µ�Ԫ�ر�ԭ���Ĵ���ִ���³�����