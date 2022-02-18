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

typedef struct Dist{
    int next;
    int weight;
    bool inQueue=false;
}Dist;

typedef struct IndexPriorityQueue{
    Dist dist;
    int pm=-1;
    int im=-1;
}IPQ;

/**
 * �������ȶ��еĺ���
 */
void push(int ki,int &length,Dist dist,IPQ queue[]);
void pop(int &length,int ki,IPQ queue[]); //�������ȶ��г��Ӳ���
void swim(int length,IPQ queue[]); //�ڶ��в������ݺ���ϸ�����
void sink(int root,IPQ queue[],int length); //�ڶ���ɾ�����ݺ���³�����
bool decreaseKey(int ki,Dist dist,IPQ queue[]); //������µ�Ԫ�ر�ԭ����С,��ִ���ϸ�����
void swap(int i,int j,IPQ queue[]);
bool smaller(int i,int j,IPQ queue[]); //�Ƚϱߵ�Ȩֵ

/**
 * Dijkstra�㷨����Ҫ�ĺ���
 */
void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]); //�����ڽӱ�
void displayAdjacencyList(ArrayV arrayV[],int length);
void eagerDijkstra(IPQ queue[],ArrayV arrayV[],int &length,int arrayDist[],int prev[]);
void findPath(int prev[],int end,int numV);


int main(){
    ArrayV arrayV[255];
    int numV;
    cout<<"���붥�����:";
    cin>>numV;
    IPQ *queue; //�������ȶ���
    int *prev;
    prev = new int[numV]{};
    queue = new IPQ[100]{};
    int *arrayDist;
    arrayDist = new int[numV]{};
    int length=0; //���еĳ���
    queue[0].dist.next=0;
    queue[0].dist.weight=0;
    createAdjacencyListAndEdgeList(numV,arrayV);
    int star=0;
    int edgeNum=arrayV[star].length;
    for(int i=0;i<edgeNum;i++){
        int next=arrayV[star].arrayE[i].next;
        Dist d;
        d.next=next;
        d.weight=arrayV[star].arrayE[i].weight;
        d.inQueue=true;
        push(d.next,length,d,queue);
        arrayDist[d.next]=d.weight;
        arrayV[star].flag=true;
    }
    arrayDist[star]=0;

    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    QueryPerformanceCounter(&nBeginTime);
    eagerDijkstra(queue,arrayV,length,arrayDist,prev);
    QueryPerformanceCounter(&nEndTime);

    for(int i=0;i<numV;i++) cout<<arrayDist[i]<<" ";
    cout<<endl;
    cout<<"��Դ���·������:"<<endl;
    for(int e=0;e<numV;e++){
        if(e==star) continue;
        cout<<star<<"->"<<e<<":";
        findPath(prev,e,numV);
        cout<<endl;
    }
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"����ʱ��:"<<time*1000<<"ms";
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
    cout<<"�ڽӱ��������,Dist��������:"<<endl;
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

void eagerDijkstra(IPQ queue[],ArrayV arrayV[],int &length,int arrayDist[],int prev[]){
    while(length!=0){
        Dist dist=queue[queue[0].im].dist; //dist:(2,1) dist.next=2
        int begin=dist.next;
        int edgeNum=arrayV[begin].length;
        if(arrayV[begin].flag==false){
            arrayV[begin].flag=true;
            for(int i=0;i<edgeNum;i++){
                int end=arrayV[begin].arrayE[i].next; //end=1,4 weight=4,13
                int weight=arrayDist[dist.next]+arrayV[begin].arrayE[i].weight;
                Dist d; //d:(1,4),(4,13)
                d.next=end;
                d.weight=weight;
                d.inQueue=true;
                if(arrayV[end].flag==false){
                    if(queue[end].dist.inQueue==true){
                        if(decreaseKey(end,d,queue)){ //�ýڵ�֮ǰ�����ʹ������Ը���
                            arrayDist[d.next]=d.weight;
                            prev[d.next]=begin;
                        }
                    }
                    if(queue[end].dist.inQueue==false){
                        push(end,length,d,queue); //�ýڵ�֮ǰû�����ʹ�������ֱ�Ӳ���
                        arrayDist[d.next]=d.weight;
                        prev[d.next]=begin;
                    }
                }
            }
        }
        pop(length,queue[0].im,queue);
    }
}

void findPath(int prev[],int end,int numV){
    for(int i=end;i>=0&&i<numV;){
        if(i==0){
            cout<<i;
            break;
        }
        cout<<i<<"-";
        i=prev[i];
    }
}

void push(int ki,int &length,Dist dist,IPQ queue[]){
    queue[ki].dist=dist;
    queue[ki].pm=length;
    queue[length].im=ki;
    swim(length,queue);
    length++;
}

void pop(int &length,int ki,IPQ queue[]){
    int i=queue[ki].pm;
    swap(i,length-1,queue);
    length--;
    sink(i,queue,length);
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

bool decreaseKey(int ki,Dist dist,IPQ queue[]){
    if(queue[ki].dist.weight>dist.weight){
        queue[ki].dist=dist;
        swim(queue[ki].pm,queue);
        return true;
    }
    return false;
}

void swap(int i,int j,IPQ queue[]){
    queue[queue[j].im].pm=i;
    queue[queue[i].im].pm=j;
    int tmp=queue[i].im;
    queue[i].im=queue[j].im;
    queue[j].im=tmp;
}

bool smaller(int i,int j,IPQ queue[]){ //i=1 j=0
    if(queue[queue[i].im].dist.weight<queue[queue[j].im].dist.weight) return true; //ע������Ҫͨ��heap��queue��ӳ��im���Ƚϴ�С
    else return false;
}