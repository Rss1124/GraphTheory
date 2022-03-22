#include <iostream>
#include <windows.h>
using namespace std;

typedef struct Edge{
    int begin;
    int end;
    int flow=0;
    int capacity=0;
    int residualEnd;
}Edge;

typedef struct ArrayE{
    Edge edge;
}ArrayE;

typedef struct ArrayV{
    ArrayE arrayE[255];
    int length=0;
    int visited=0;
}ArrayV;

void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]); //生成邻接表
void displayAdjacencyList(ArrayV arrayV[],int length);
int remainingCapacity(int capacity,int flow);
int dfs(int node,long flow,int t,ArrayV arrayV[],int &visitedToken);
int min(int flow,int remainingCapacity);

int main(){

    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    ArrayV arrayV[255];
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    int visitedToken=1;
    int maxFlow=0;
    createAdjacencyListAndEdgeList(numV,arrayV);
    cout<<endl;
    int s=0,t=numV-1;

    QueryPerformanceCounter(&nBeginTime);

    for(long f=dfs(s,9999,t,arrayV,visitedToken);f!=0;f=dfs(s,9999,t,arrayV,visitedToken)){
        visitedToken++;
        maxFlow+=f;
    }

    QueryPerformanceCounter(&nEndTime);

    cout<<"maxFlow:"<<maxFlow<<endl;

    displayAdjacencyList(arrayV,numV);

    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"运行时间:"<<time*1000<<"ms";
}

void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]){
    for(int i=0;i<numV;i++){
        int numE;
        int length=arrayV[i].length;
        cout<<"输入与第"<<i<<"号顶点相连的顶点个数:";
        cin>>numE;
        for(int j=length;j<length+numE;j++){
            int v,c;
            cout<<"输入与第"<<i<<"号顶点相连的具体顶点的编号以及对应的容量:";
            cin>>v>>c;
            Edge e1,e2;
            e1.begin=i; //i=4
            e1.end=v; //v=7
            e1.capacity=c;
            e1.residualEnd=arrayV[v].length;
            e2.begin=v; //v=7
            e2.end=i; //i=4
            e2.residualEnd=arrayV[i].length;
            e2.capacity=0;
            arrayV[i].arrayE[j].edge=e1;
            arrayV[i].length++;
            arrayV[v].arrayE[arrayV[v].length].edge=e2;
            arrayV[v].length++;
            cout<<"第"<<i<<"号顶点与第"<<v<<"号顶点成功相连"<<endl;
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"邻接表生成完毕"<<endl;
}

void displayAdjacencyList(ArrayV arrayV[],int length){
    for(int i=0;i<length;i++){
        cout<<i;
        for(int j=0;j<arrayV[i].length;j++){
            cout<<"->"<<arrayV[i].arrayE[j].edge.end<<"("<<arrayV[i].arrayE[j].edge.flow<<"/"<<arrayV[i].arrayE[j].edge.capacity<<")"<<"["<<arrayV[i].arrayE[j].edge.residualEnd<<"]";
        }
        cout<<endl;
    }
}

int remainingCapacity(int capacity,int flow){
    return capacity-flow;
}

/**
 * 通过dfs找寻起点到终点的路径,同时找寻其中的minflow,最后在回溯的时候对路径上的flow进行更新
 */
int dfs(int node,long flow,int t,ArrayV arrayV[],int &visitedToken){
    if(node==t) return flow;
    arrayV[node].visited=visitedToken;
    int length=arrayV[node].length;
    for(int i=0;i<length;i++){
        Edge edge=arrayV[node].arrayE[i].edge;
        if(remainingCapacity(edge.capacity,edge.flow)>0&&arrayV[edge.end].visited!=visitedToken){
            long bottleNeck= dfs(edge.end,min(flow,remainingCapacity(edge.capacity,edge.flow)),t,arrayV,visitedToken); //minflow
            if(bottleNeck>0){
                arrayV[node].arrayE[i].edge.flow+=bottleNeck; //更新edge上的flow
                arrayV[edge.end].arrayE[edge.residualEnd].edge.flow-=bottleNeck; //更新residualedge上的flow
                return bottleNeck;
            }
        }
    }
    return 0;
}

int min(int flow,int remainingCapacity){
    if(flow<remainingCapacity) return flow;
    else return remainingCapacity;
}