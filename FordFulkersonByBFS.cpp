#include <iostream>
#include <queue>
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
    int pre=-1;
    bool visited=false;
}ArrayV;

void createAdjacencyListAndEdgeList(int numV,ArrayV arrayV[]); //生成邻接表
void displayAdjacencyList(ArrayV arrayV[],int length);
int remainingCapacity(int capacity,int flow);
int min(int flow,int remainingCapacity);
bool bfs(queue<int> &queue,int t,ArrayV arrayV[]);
void findMaxFlow(int s,int t,ArrayV arrayV[],int numV,int &maxFlow);

int main(){

    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    ArrayV arrayV[255]{};
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    int maxFlow=0;
    createAdjacencyListAndEdgeList(numV,arrayV);
    int s=0,t=numV-1;

    QueryPerformanceCounter(&nBeginTime);
    findMaxFlow(s,t,arrayV,numV,maxFlow);
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

int min(int flow,int remainingCapacity){
    if(flow<remainingCapacity) return flow;
    else return remainingCapacity;
}

/** 从原点出发找寻能通往终点的路径 **/
bool bfs(queue<int> &q,int t,ArrayV arrayV[]){
    while(q.empty()!=true){
        int now=q.front();
        q.pop();
        if(now==t){
            return true;
        }
        ArrayV begin=arrayV[now];
        for(int i=0;i<begin.length;i++){
            if(remainingCapacity(begin.arrayE[i].edge.capacity,begin.arrayE[i].edge.flow)>0&&arrayV[begin.arrayE[i].edge.end].visited==false){
                arrayV[begin.arrayE[i].edge.end].pre=begin.arrayE[i].edge.residualEnd;
                q.push(begin.arrayE[i].edge.end);
                arrayV[begin.arrayE[i].edge.end].visited=true;
            }
        }
    }
    return false;
}

/** 根据bfs找到的路径,对其进行逆向遍历,从而更新flow **/
void findMaxFlow(int s,int t,ArrayV arrayV[],int numV,int &maxFlow){
    queue<int> q;
    q.push(s);
    arrayV[s].visited=true;
    while(bfs(q,t,arrayV)==true){
        q=queue<int>();
        int minFlow=99999;
        /** 找寻路径上的最小flow **/
        for(int endIndex=t;endIndex!=s;){
            int beginIndex=arrayV[endIndex].pre; //0
            Edge edge=arrayV[endIndex].arrayE[beginIndex].edge; //10->7
            int residualBeginIndex=edge.end; //7
            int residualEndIndex=edge.residualEnd; //2
            Edge residualEdge=arrayV[residualBeginIndex].arrayE[residualEndIndex].edge; //7->10
            minFlow=min(minFlow, remainingCapacity(residualEdge.capacity,residualEdge.flow));
            endIndex=residualBeginIndex;
        }
        /** 更新路径上的flow **/
        for(int endIndex=t;endIndex!=s;){
            int beginIndex=arrayV[endIndex].pre; //0
            Edge edge=arrayV[endIndex].arrayE[beginIndex].edge; //10->7
            arrayV[endIndex].arrayE[beginIndex].edge.flow-=minFlow;
            int residualBeginIndex=edge.end; //7
            int residualEndIndex=edge.residualEnd; //2
            arrayV[residualBeginIndex].arrayE[residualEndIndex].edge.flow+=minFlow;
            endIndex=residualBeginIndex;
        }
        /** 重置顶点的访问情况 **/
        for(int i=0;i<numV;i++){
            arrayV[i].visited=false;
            arrayV[i].pre=-1;
        }
        q.push(s);
        arrayV[s].visited=true;
        maxFlow+=minFlow;
    }
}