#include <iostream>

using namespace std;

/** 邻接表 **/
typedef struct Array{
    int arrayE[255];
    int length=0;
    bool flag=false;
}Array;

void displayAdjacencyList(Array arrayV[],int length);
void adjacencyList();
bool dfsLabel(Array arrayV[],int num,int &value,int arrayColor[],int pre); //(有向图&&无向图)邻接表的DFS
void findBridge(Array arrayV[],int length,int arrayColor[]);

int main() {
    adjacencyList();
}

void adjacencyList(){
    Array arrayV[255];
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
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
            cout<<"第"<<i<<"号顶点与第"<<v<<"号顶点成功相连"<<endl;
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"邻接表生成完毕！染色情况如下:"<<endl;
    int *arrayColor;
    arrayColor=new int[numV]{};
    int value=0;
    for(int i=0;i<numV;i++){
        dfsLabel(arrayV,i,value,arrayColor,0);
    }
    for(int i=0;i<numV;i++) cout<<arrayColor[i]<<" ";
    cout<<endl;
    cout<<"割边情况如下:"<<endl;
    findBridge(arrayV,numV,arrayColor);
}

bool dfsLabel(Array arrayV[],int num,int &value,int arrayColor[],int pre){ //num=0 pre=2
    if(arrayV[num].flag==true){ //case1:访问到“被访问的顶点”且ID[num]比ID[pre]小
        if(arrayColor[num]<arrayColor[pre]) arrayColor[pre]=arrayColor[num];
    }
    if(arrayV[num].flag==false){
        arrayColor[num]=value++;
        arrayV[num].flag=true;
        for(int i=0;i<arrayV[num].length;i++){
            if(arrayV[num].arrayE[i]!=pre){ //防止无向图出现以下这种情况 3->2 2->3
                dfsLabel(arrayV,arrayV[num].arrayE[i],value,arrayColor,num);
                if(arrayColor[arrayV[num].arrayE[i]]<arrayColor[num]) arrayColor[num]=arrayColor[arrayV[num].arrayE[i]];
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

void findBridge(Array arrayV[],int length,int arrayColor[]){
    for(int i=0;i<length;i++){
        for(int j=0;j<arrayV[i].length;j++){
            if(arrayColor[i]<arrayColor[arrayV[i].arrayE[j]]) cout<<i<<"-"<<arrayV[i].arrayE[j]<<endl;
        }
    }
}