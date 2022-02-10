#include <iostream>
#include <vector>
using namespace std;

typedef struct Array{
    int arrayE[255];
    int length=0;
    bool flag=false;
}Array;

typedef struct Edge{
    int begin;
    int end;
    bool visited=false;
}Edge;

void undirectedGraph();
void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE,int arrayDegree[]); //生成邻接表和边表
void findBegin(int &begin,int arrayDegree[],int numV); //找欧拉回路的起点和终点
void findEulerPath(int index,int arrayDegree[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE,int pre);
void displayAdjacencyList(Array arrayV[],int length);
bool checkNext(vector<Edge>&arrayE,int begin,int next);

int main(){
    undirectedGraph();
}

void undirectedGraph(){
    vector<Edge>arrayE;
    Array arrayV[255];
    int numV;
    int numE;
    cout<<"输入顶点个数以及边的个数:";
    cin>>numV>>numE;
    int temp=numE;
    int *arrayDegree;
    int *tourV;
    arrayDegree=new int[numV]{};
    tourV=new int[numE+1]{};
    createAdjacencyListAndEdgeList(numV,arrayV,arrayE,arrayDegree);
    int begin=-1;
    cout<<endl;
    findBegin(begin,arrayDegree,numV);
    findEulerPath(begin,arrayDegree,arrayV,arrayE,tourV,numE,-1);
    cout<<"欧拉路径如下:"<<endl;
    for(int i=0;i<=temp;i++) cout<<tourV[i]<<" ";
}

void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE,int arrayDegree[]){
    for(int i=0;i<numV;i++){
        int numE;
        cout<<"输入与第"<<i<<"号顶点相连的顶点个数:";
        cin>>numE;
        for(int j=0;j<numE;j++){
            int v;
            cout<<"输入与第"<<i<<"号顶点相连的具体顶点的编号:";
            cin>>v;
            arrayV[i].arrayE[j]=v;
            arrayV[i].length++;
            arrayDegree[i]++;
            cout<<"第"<<i<<"号顶点与第"<<v<<"号顶点成功相连"<<endl;
            Edge e;
            e.begin=i;
            e.end=v;
            arrayE.push_back(e);
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"邻接表生成完毕！"<<endl;
    vector<Edge>::iterator it;
    for(it=arrayE.begin();it!=arrayE.end();it++){
        cout<<it->begin<<"->"<<it->end<<endl;
    }
    cout<<"边表生成完毕"<<endl;
    for(int i=0;i<numV;i++) cout<<arrayDegree[i]<<" ";
}

void findBegin(int &begin,int arrayDegree[],int numV){
    int flag=0;
    for(int i=0;i<numV;i++){
        if(arrayDegree[i]%2!=0){
            begin=i;
            flag++;
        }
    }
    if(flag==0){
        cout<<"有欧拉回路"<<endl;
    }
    if(flag==2){
        cout<<"有欧拉路径,起点为:"<<begin<<endl;
    }
    else cout<<"什么都没有"<<endl;
}

void findEulerPath(int index,int arrayDegree[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE,int pre){ //index=0 pre=1
    for(int i=0;i<arrayV[index].length;i++){
        int next=arrayV[index].arrayE[i];
        if(checkNext(arrayE,index,next)==true&&next!=pre){
            /**
             * 注意，无向图访问一条边时，起点index和终点next的度都要-1，并且在邻接表里要将重复的边排除，比如3->0和0->3（next==pre）
             */
            arrayDegree[index]--;
            arrayDegree[next]--;
            findEulerPath(next,arrayDegree,arrayV,arrayE,tourV,numE,index);
        }
        if(checkNext(arrayE,index,next)==false) continue;
    }
    if(arrayDegree[index]==0){
        tourV[numE--]=index;
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

bool checkNext(vector<Edge>&arrayE,int begin,int next){
    vector<Edge>::iterator it;
    for(it=arrayE.begin();it!=arrayE.end();it++){
        if(it->begin==begin&&it->end==next){
            if(it->visited==false){
                it->visited=true;
                return true; //begin->next这条边没被访问过,并将其标记为已访问
            }
        }
    }
    return false;
}
