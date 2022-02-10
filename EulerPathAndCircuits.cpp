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

void directedGraph();
void createAdjacencyListAndEdgeList(int numV,Array array[],vector<Edge>&arrayE,int arrayIn[],int arrayOut[]); //生成邻接表和边表
void findBeginAndEnd(int &begin,int &end,int arrayIn[],int arrayOut[],int numV); //找欧拉回路的起点和终点
void findEulerPath(int index,int arrayOut[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE);
void displayAdjacencyList(Array arrayV[],int length);
bool checkNext(vector<Edge>&arrayE,int begin,int next);

int main(){
    directedGraph();
}

void directedGraph(){
    vector<Edge>arrayE;
    Array arrayV[255];
    int numV;
    int numE;
    cout<<"输入顶点个数以及边的个数:";
    cin>>numV>>numE;
    int temp=numE;
    int *arrayIn;
    int *arrayOut;
    int *tourV;
    arrayIn=new int[numV]{};
    arrayOut=new int[numV]{};
    tourV=new int[numE+1]{};
    createAdjacencyListAndEdgeList(numV,arrayV,arrayE,arrayIn,arrayOut);
    int begin=-1;
    int end=-1;
    findBeginAndEnd(begin,end,arrayIn,arrayOut,numV);
    findEulerPath(begin,arrayOut,arrayV,arrayE,tourV,numE);
    cout<<"欧拉路径如下:"<<endl;
    for(int i=0;i<=temp;i++) cout<<tourV[i]<<" ";
}

void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE,int arrayIn[],int arrayOut[]){
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
            arrayOut[i]++;
            arrayIn[v]++;
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
    for(int i=0;i<numV;i++) cout<<arrayIn[i]<<" ";
    cout<<endl;
    for(int i=0;i<numV;i++) cout<<arrayOut[i]<<" ";
    cout<<endl;
}

void findBeginAndEnd(int &begin,int &end,int arrayIn[],int arrayOut[],int numV){
    int beginState=0;
    int endState=0;
    for(int i=0;i<numV;i++){
        if(arrayIn[i]-arrayOut[i]>1||arrayOut[i]-arrayIn[i]>1){
            beginState=-1;
            endState=-1;
            break;
        }
        else if(arrayOut[i]-arrayIn[i]==1) begin=i,beginState++;
        else if(arrayIn[i]-arrayOut[i]==1) end=i,endState++;
    }
    if(beginState==0&&endState==0){
        begin=0;
        end=0;
        cout<<"有欧拉回路"<<endl;
    }
    if(beginState==1&&endState==1){
        cout<<"有欧拉路径,起点为:"<<begin<<",终点为:"<<end<<endl;
    }
    if(beginState==-1&&endState==-1) cout<<"没有欧拉路径"<<endl;
}

void findEulerPath(int index,int arrayOut[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE){ //index=1
    for(int i=0;i<arrayV[index].length;i++){
        int next=arrayV[index].arrayE[i];
        if(checkNext(arrayE,index,next)==true){
            arrayOut[index]--;
            findEulerPath(next,arrayOut,arrayV,arrayE,tourV,numE);
        }
        if(checkNext(arrayE,index,next)==false) continue;
    }
    if(arrayOut[index]==0){
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

