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
 * 索引优先队列的函数
 */
void push(int ki,int &length,Dist dist,IPQ queue[]);
void pop(int &length,int ki,IPQ queue[]); //索引优先队列出队操作
void swim(int length,IPQ queue[]); //在堆中插入数据后的上浮操作
void sink(int root,IPQ queue[],int length); //在堆中删除数据后的下沉操作
bool decreaseKey(int ki,Dist dist,IPQ queue[]); //如果更新的元素比原来的小,则执行上浮操作
void swap(int i,int j,IPQ queue[]);
bool smaller(int i,int j,IPQ queue[]); //比较边的权值

/**
 * Dijkstra算法所需要的函数
 */
void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]); //生成邻接表
void displayAdjacencyList(ArrayV arrayV[],int length);
void eagerDijkstra(IPQ queue[],ArrayV arrayV[],int &length,int arrayDist[],int prev[]);
void findPath(int prev[],int end,int numV);


int main(){
    ArrayV arrayV[255];
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    IPQ *queue; //索引优先队列
    int *prev;
    prev = new int[numV]{};
    queue = new IPQ[100]{};
    int *arrayDist;
    arrayDist = new int[numV]{};
    int length=0; //队列的长度
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
    cout<<"单源最短路径如下:"<<endl;
    for(int e=0;e<numV;e++){
        if(e==star) continue;
        cout<<star<<"->"<<e<<":";
        findPath(prev,e,numV);
        cout<<endl;
    }
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"运行时间:"<<time*1000<<"ms";
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
    cout<<"邻接表生成完毕,Dist数组如下:"<<endl;
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
                        if(decreaseKey(end,d,queue)){ //该节点之前被访问过，尝试更新
                            arrayDist[d.next]=d.weight;
                            prev[d.next]=begin;
                        }
                    }
                    if(queue[end].dist.inQueue==false){
                        push(end,length,d,queue); //该节点之前没被访问过，所以直接插入
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
    if(queue[queue[i].im].dist.weight<queue[queue[j].im].dist.weight) return true; //注意这里要通过heap到queue的映射im来比较大小
    else return false;
}