#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

typedef struct ArrayE{
    int next;
    int weight;
}ArrayE;

typedef struct ArrayV{
    ArrayE arrayE[255];
    int length=0;
    int flag=false;
}ArrayV;

typedef struct Edge{
    int begin;
    int end;
    int weight;
    bool inQueue=false;
}Edge;

typedef struct IndexPriorityQueue{
    Edge edge;
    int pm=-1;
    int im=-1;
}IPQ;

/**
 * �������ȶ��еĺ���
 */
void push(int ki,int &length,Edge edge,IPQ queue[]);
void pop(int &length,int ki,IPQ queue[]); //�������ȶ��г��Ӳ���
void swim(int length,IPQ queue[]); //�ڶ��в������ݺ���ϸ�����
void sink(int root,IPQ queue[],int length); //�ڶ���ɾ�����ݺ���³�����
void update(int ki,Edge edge,IPQ queue[],int length); //���¶��е�Ԫ��
void decreaseKey(int ki,Edge edge,IPQ queue[]); //������µ�Ԫ�ر�ԭ����С,��ִ���ϸ�����
void swap(int i,int j,IPQ queue[]);
bool smaller(int i,int j,IPQ queue[]); //�Ƚϱߵ�Ȩֵ

/**
 * Prim�㷨����Ҫ�ĺ���
 */
void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]); //�����ڽӱ�ͱ߱�
void displayAdjacencyList(ArrayV arrayV[],int length);
void findMST(IPQ queue[],ArrayV arrayV[],int &length);

int main(){
    ArrayV arrayV[255];
    int numV;
    cout<<"���붥�����:";
    cin>>numV;
    IPQ *queue; //�������ȶ���
    queue = new IPQ[100];
    int length=0; //���еĳ���
    queue[0].edge.begin=0;
    queue[0].edge.end=0;
    queue[0].edge.weight=9999;
    createAdjacencyListAndEdgeList(numV,arrayV);
    vector<Edge>::iterator it;
    int star=0;
    int edgeNum=arrayV[star].length;
    for(int i=0;i<edgeNum;i++){
        int next=arrayV[star].arrayE[i].next;
        Edge e;
        e.begin=star;
        e.end=next;
        e.weight=arrayV[star].arrayE[i].weight;
        e.inQueue=true;
        push(e.end,length,e,queue);
        arrayV[e.begin].flag=true;
    }

    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    QueryPerformanceCounter(&nBeginTime);
    findMST(queue,arrayV,length);
    QueryPerformanceCounter(&nEndTime);

    for(int i=0;i<numV;i++){
        if(queue[i].edge.inQueue==true) cout<<"("<<i<<")"<<"-("<<queue[i].edge.begin<<","<<queue[i].edge.end<<","<<queue[i].edge.weight<<")-"<<"("<<queue[i].pm<<")"<<"-"<<"("<<queue[i].im<<")"<<endl;
        else cout<<"("<<i<<")"<<"-(null)-"<<"("<<queue[i].pm<<")"<<"-"<<"("<<queue[i].im<<")"<<endl;
    }
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"����ʱ��:"<<time*1000<<"ms";
}

void push(int ki,int &length,Edge edge,IPQ queue[]){
    queue[ki].edge=edge;
    queue[ki].pm=length;
    queue[length].im=ki;
    swim(length,queue);
    length++;
}

void pop(int &length,int ki,IPQ queue[]){
    int i=queue[ki].pm;
    swap(i,length-1,queue);
    length--;
    sink(i,queue,length); //i=0,length=12
    queue[ki].pm=-1;
    queue[length].im=-1;
}

void swim(int length,IPQ queue[]){
    for(int i=(length-1)/2;length>0&&smaller(length,i,queue)==true;){ //length=1 i=0
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


void decreaseKey(int ki,Edge edge,IPQ queue[]){
    if(edge.weight<queue[ki].edge.weight){
        queue[ki].edge=edge;
        swim(queue[ki].pm,queue);
    }
}

void swap(int i,int j,IPQ queue[]){
    queue[queue[j].im].pm=i;
    queue[queue[i].im].pm=j;
    int tmp=queue[i].im;
    queue[i].im=queue[j].im;
    queue[j].im=tmp;
}

bool smaller(int i,int j,IPQ queue[]){ //i=1 j=0
    if(queue[queue[i].im].edge.weight<queue[queue[j].im].edge.weight) return true; //ע������Ҫͨ��heap��queue��ӳ��im���Ƚϴ�С
    else return false;
}

void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]){
    for(int i=0;i<numV;i++){
        int numE;
        cout<<"�������"<<i<<"�Ŷ��������Ķ������:";
        cin>>numE;
        for(int j=0;j<numE;j++){
            int v,w;
            cout<<"�������"<<i<<"�Ŷ��������ľ��嶥��ı���Լ���Ӧ��Ȩֵ:";
            cin>>v>>w;
            arrayV[i].arrayE[j].next=v;
            arrayV[i].arrayE[j].weight=w;
            arrayV[i].length++;
            cout<<"��"<<i<<"�Ŷ������"<<v<<"�Ŷ���ɹ�����"<<endl;
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"�ڽӱ�������ϣ�MST����:"<<endl;
}

void displayAdjacencyList(ArrayV arrayV[],int length){
    for(int i=0;i<length;i++){
        cout<<i;
        for(int j=0;j<arrayV[i].length;j++){
            cout<<"->"<<arrayV[i].arrayE[j].next<<"("<<arrayV[i].arrayE[j].weight<<")";
        }
        cout<<endl;
    }
}

void findMST(IPQ queue[],ArrayV arrayV[],int &length){
    while(length!=0){
        Edge edge=queue[queue[0].im].edge; //edge:(0,2,0)
        pop(length,queue[0].im,queue);
        int begin=edge.end; //begin=2
        int edgeNum=arrayV[begin].length;
        if(arrayV[begin].flag==false){
            arrayV[begin].flag=true;
            for(int i=0;i<edgeNum;i++){
                int end=arrayV[begin].arrayE[i].next; //end=5
                int weight=arrayV[begin].arrayE[i].weight; //weight=6
                Edge e; //e:(2,5,6)
                e.begin=begin;
                e.end=end;
                e.weight=weight;
                e.inQueue=true;
                if(arrayV[end].flag==false){ //���Է�����һ���ڵ�
                    if(queue[end].edge.inQueue==true) decreaseKey(end,e,queue); //�ýڵ�֮ǰ�����ʹ������Ը���
                    if(queue[end].edge.inQueue==false) push(end,length,e,queue); //�ýڵ�֮ǰû�����ʹ�������ֱ�Ӳ���
                }
            }
        }
    }
}