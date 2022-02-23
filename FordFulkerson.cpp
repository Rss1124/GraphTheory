#include <iostream>
using namespace std;

typedef struct Edge{
    int begin;
    int end;
    int flow=0;
    int capacity=0;
    struct Edge *residual;
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
void augment(long bottleNeck,Edge &edge);
int dfs(int node,long flow,int t,ArrayV arrayV[],int &visitedToken);
int min(int flow,int remainingCapacity);

int main(){
    ArrayV arrayV[255];
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    int visitedToken=1;
    int maxFlow=0;
    createAdjacencyListAndEdgeList(numV,arrayV);
    cout<<endl;
    int s=0,t=numV-1;
    for(long f=dfs(s,9999,t,arrayV,visitedToken);f!=0;f=dfs(s,9999,t,arrayV,visitedToken)){
        displayAdjacencyList(arrayV,numV);
        cout<<endl;
        visitedToken++;
        maxFlow+=f;
    }
//    cout<<maxFlow;
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
            e1.begin=i;
            e1.end=v;
            e1.capacity=c;
            e2.begin=v;
            e2.end=i;
            e2.capacity=0;
            e1.residual=&e2;
            e2.residual=&e1;
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
            cout<<"->"<<arrayV[i].arrayE[j].edge.end<<"("<<arrayV[i].arrayE[j].edge.flow<<"/"<<arrayV[i].arrayE[j].edge.capacity<<")";
        }
        cout<<endl;
    }
}

int remainingCapacity(int capacity,int flow){
    return capacity-flow;
}

void augment(long bottleNeck,Edge &edge){
    edge.flow+=bottleNeck;
//    edge.residual->flow-=bottleNeck;
}

int dfs(int node,long flow,int t,ArrayV arrayV[],int &visitedToken){
    if(node==t) return flow;
    arrayV[node].visited=visitedToken;
    int length=arrayV[node].length;
    for(int i=0;i<length;i++){
        Edge edge=arrayV[node].arrayE[i].edge;
        if(remainingCapacity(edge.capacity,edge.flow)>0&&arrayV[edge.end].visited!=visitedToken){
            long bottleNeck= dfs(edge.end,min(flow,remainingCapacity(edge.capacity,edge.flow)),t,arrayV,visitedToken);
            if(bottleNeck>0){
                arrayV[node].arrayE[i].edge.flow+=bottleNeck;
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