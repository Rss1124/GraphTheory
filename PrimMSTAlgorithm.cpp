#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct Array{
    int arrayE[255];
    int length=0;
    int flag=false;
}Array;

typedef struct Edge{
    int begin;
    int end;
    int weight;
    bool operator < (const Edge & edge) const{ //重载"<"符号，让优先队列按照weight从小到大排序
        return weight>edge.weight;
    }
}Edge;

void lazyPrim();
void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE); //生成邻接表和边表
void displayAdjacencyList(Array arrayV[],int length);
void findMSTByLazyPrim(priority_queue<Edge> &pq,int numV,Array arrayV[],vector<Edge>&arrayE,Edge MST[],int &index);

int main(){
    lazyPrim();
}

void lazyPrim(){
    priority_queue<Edge> pq; //从小到大的优先队列
    vector<Edge>arrayE;
    Array arrayV[255];
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    Edge *MST;
    MST =new Edge[numV-1];
    createAdjacencyListAndEdgeList(numV,arrayV,arrayE);
    vector<Edge>::iterator it;
    for(it=arrayE.begin();it!=arrayE.end();it++){
        if(it->begin==0){
            Edge e;
            e.begin=it->begin;
            e.end=it->end;
            e.weight=it->weight;
            pq.push(e);
            arrayV[e.begin].flag=true;
        }
    }
    int index=0;
    findMSTByLazyPrim(pq,numV,arrayV,arrayE,MST,index);
    cout<<"最小生成树如下:"<<endl;
    for(int i=0;i<numV-1;i++) cout<<MST[i].begin<<"->"<<MST[i].end<<"("<<MST[i].weight<<")"<<endl;
}

void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE){
    for(int i=0;i<numV;i++){
        int numE;
        cout<<"输入与第"<<i<<"号顶点相连的顶点个数:";
        cin>>numE;
        for(int j=0;j<numE;j++){
            int v,w;
            cout<<"输入与第"<<i<<"号顶点相连的具体顶点的编号以及对应的权值:";
            cin>>v>>w;
            arrayV[i].arrayE[j]=v;
            arrayV[i].length++;
            cout<<"第"<<i<<"号顶点与第"<<v<<"号顶点成功相连"<<endl;
            Edge e;
            e.begin=i;
            e.end=v;
            e.weight=w;
            arrayE.push_back(e);
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"邻接表生成完毕！"<<endl;
    vector<Edge>::iterator it;
    for(it=arrayE.begin();it!=arrayE.end();it++){
        cout<<it->begin<<"->"<<it->end<<"("<<it->weight<<")"<<endl;
    }
    cout<<"边表生成完毕"<<endl;
}

void findMSTByLazyPrim(priority_queue<Edge> &pq,int numV,Array arrayV[],vector<Edge>&arrayE,Edge MST[],int &index){
    while(!pq.empty()){
        vector<Edge>::iterator it;
        Edge e=pq.top();
        int next=e.end;
        pq.pop();
        if(arrayV[next].flag==false){
            MST[index].begin=e.begin;
            MST[index].end=e.end;
            MST[index].weight=e.weight;
            index++;
            if(index==numV-1) break;
            arrayV[next].flag=true;
            for(it=arrayE.begin();it!=arrayE.end();it++){
                if(it->begin==next){
                    Edge e;
                    e.begin=it->begin;
                    e.end=it->end;
                    e.weight=it->weight;
                    if(arrayV[e.end].flag==false){
                        pq.push(e);
                        arrayV[e.begin].flag=true;
                    }
                }
            }
        }
    }
}

void displayAdjacencyList(Array arrayV[],int length){
    for(int i=0;i<length;i++){
        cout<<i;
        for(int j=0;j<arrayV[i].length;j++){
            cout<<"->"<<arrayV[i].arrayE[j];
        }
        cout<<endl;
    }
}