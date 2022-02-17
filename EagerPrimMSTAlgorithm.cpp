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
 * 索引优先队列的函数
 */
void push(int ki,int &length,Edge edge,IPQ queue[]);
void pop(int &length,int ki,IPQ queue[]); //索引优先队列出队操作
void swim(int length,IPQ queue[]); //在堆中插入数据后的上浮操作
void sink(int root,IPQ queue[],int length); //在堆中删除数据后的下沉操作
void update(int ki,Edge edge,IPQ queue[],int length); //更新队列的元素
void decreaseKey(int ki,Edge edge,IPQ queue[]); //如果更新的元素比原来的小,则执行上浮操作
void swap(int i,int j,IPQ queue[]);
bool smaller(int i,int j,IPQ queue[]); //比较边的权值

/**
 * Prim算法所需要的函数
 */
void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]); //生成邻接表和边表
void displayAdjacencyList(ArrayV arrayV[],int length);
void findMST(IPQ queue[],ArrayV arrayV[],int &length);

int main(){
    ArrayV arrayV[255];
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    IPQ *queue; //索引优先队列
    queue = new IPQ[100];
    int length=0; //队列的长度
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
    cout<<"运行时间:"<<time*1000<<"ms";
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
    if(queue[queue[i].im].edge.weight<queue[queue[j].im].edge.weight) return true; //注意这里要通过heap到queue的映射im来比较大小
    else return false;
}

void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]){
    for(int i=0;i<numV;i++){
        int numE;
        cout<<"输入与第"<<i<<"号顶点相连的顶点个数:";
        cin>>numE;
        for(int j=0;j<numE;j++){
            int v,w;
            cout<<"输入与第"<<i<<"号顶点相连的具体顶点的编号以及对应的权值:";
            cin>>v>>w;
            arrayV[i].arrayE[j].next=v;
            arrayV[i].arrayE[j].weight=w;
            arrayV[i].length++;
            cout<<"第"<<i<<"号顶点与第"<<v<<"号顶点成功相连"<<endl;
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"邻接表生成完毕！MST如下:"<<endl;
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
                if(arrayV[end].flag==false){ //可以访问下一个节点
                    if(queue[end].edge.inQueue==true) decreaseKey(end,e,queue); //该节点之前被访问过，尝试更新
                    if(queue[end].edge.inQueue==false) push(end,length,e,queue); //该节点之前没被访问过，所以直接插入
                }
            }
        }
    }
}