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
bool dfsLabel(Array arrayV[],int num,int &value,int arrayLow[],int arrayID[],int pre,bool inCycle[]); //邻接表存储的无向图的DFS
void findBridge(Array arrayV[],int length,int arrayLow[],int arrayID[],bool inCycle[],bool isArt[]);

int main() {
    /** 桥是无向图 **/
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
    cout<<"邻接表生成完毕！"<<endl;
    bool *inCycle;
    inCycle=new bool[numV]{};
    int *arrayLow;
    arrayLow=new int[numV]{};
    int *arrayID;
    arrayID=new int[numV]{};
    bool *isArt;
    isArt=new bool[numV]{};
    int value=0;
    for(int i=0;i<numV;i++){
        dfsLabel(arrayV,i,value,arrayLow,arrayID,0,inCycle);
    }
    cout<<"顶点索引: ";
    for(int i=0;i<numV;i++) cout<<arrayID[i]<<" ";
    cout<<endl;
    cout<<"染色情况: ";
    for(int i=0;i<numV;i++) cout<<arrayLow[i]<<" ";
    cout<<endl;
    cout<<"是否在环: ";
    for(int i=0;i<numV;i++) cout<<inCycle[i]<<" ";
    cout<<endl;
    cout<<"割边情况如下:"<<endl;
    findBridge(arrayV,numV,arrayLow,arrayID,inCycle,isArt);
    cout<<"割点情况如下:"<<endl;
    for(int i=0;i<numV;i++){
        if(isArt[i]==1) cout<<i<<" ";
    }
}

/** 将顶点进行染色 **/
bool dfsLabel(Array arrayV[],int num,int &value,int arrayLow[],int arrayID[],int pre,bool inCycle[]){
    if(arrayV[num].flag==true){ //case1:访问到“被访问的顶点”且arrayLow[被访问的顶点]比arrayLow[前一个顶点]小
        if(arrayLow[num]<arrayLow[pre]){
            arrayLow[pre]=arrayLow[num];
            inCycle[num]=true;
            inCycle[pre]=true;
        }
    }
    if(arrayV[num].flag==false){
        arrayID[num]=value;
        arrayLow[num]=arrayID[num];
        value++;
        arrayV[num].flag=true;
        for(int i=0;i<arrayV[num].length;i++){
            if(arrayV[num].arrayE[i]!=pre){ //防止无向图出现以下这种情况 3->2 2->3
                dfsLabel(arrayV,arrayV[num].arrayE[i],value,arrayLow,arrayID,num,inCycle);
                if(arrayLow[arrayV[num].arrayE[i]]<arrayLow[num]){ //case2:回溯过程中发现arrayLow[下一个顶点]比arrayLow[当前顶点]
                    arrayLow[num]=arrayLow[arrayV[num].arrayE[i]];
                    inCycle[num]=true;
                    inCycle[arrayV[num].arrayE[i]]=true;
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

void findBridge(Array arrayV[],int length,int arrayLow[],int arrayID[],bool inCycle[],bool isArt[]){
    for(int i=0;i<length;i++){
        int count=0;
        for(int j=0;j<arrayV[i].length;j++){
            if(arrayID[i]<arrayLow[arrayV[i].arrayE[j]]){ //出现割边的case:arrayID[当前顶点]<arrayLow[下一个顶点]
                cout<<i<<"-"<<arrayV[i].arrayE[j]<<endl;
            }
            if(arrayLow[i]!=arrayLow[arrayV[i].arrayE[j]]){
                count++;
                if(inCycle[i]==1) isArt[i]=1; //出现割点的case1: 处于环内的桥上的顶点
                else if(count>1) isArt[i]=1; //出现割点的case2: 没处于环内的桥上的顶点连接了2条及以上的边
            }
        }
    }
}