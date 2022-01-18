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
bool dfsAdjacencyList(Array arrayV[],int num,int arrayColor[],int color); //(有向图&&无向图)邻接表的DFS
void displayAdjacencyMatrix(int **arrayV,int length);
void adjacencyMatrix();
bool dfsAdjacencyMatrix(int **arrayV,int r,bool arrayFlag[],int num,int arrayColor[],int color); //(有向图&&无向图)邻接矩阵的DFS

int main() {
//    adjacencyList();
    adjacencyMatrix();
}

void adjacencyList(){
    Array arrayV[255];
    int numV;
    int color;
    int *arrayColor;
    arrayColor=new int[numV];
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
    cout<<"邻接表生成完毕！连通分量如下"<<endl;
    for(int i=0;i<numV;i++){
        if(arrayV[i].flag==false){
            color++;
            cout<<endl;
        }
        dfsAdjacencyList(arrayV,i,arrayColor,color);
    }
    cout<<endl;
    cout<<"连通分量的染色情况如下："<<endl;
    for(int i=0;i<numV;i++) cout<<arrayColor[i]<<" ";
}

bool dfsAdjacencyList(Array arrayV[],int num,int arrayColor[],int color){
    if(arrayV[num].flag==true) return false;
    if(arrayV[num].flag==false){
        cout<<num<<" ";
        arrayV[num].flag=true;
        arrayColor[num]=color;
        for(int i=0;i<arrayV[num].length;i++){
            dfsAdjacencyList(arrayV,arrayV[num].arrayE[i],arrayColor,color);
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


void adjacencyMatrix(){
    int numV;
    int **arrayV;
    int flag=1;
    bool *arrayFlag;
    int *arrayColor;
    int color=0;
    cout<<"输入顶点个数:";
    cin>>numV;
    arrayFlag = new bool[numV]{};
    arrayColor = new int[numV]{};
    arrayV = new int*[numV];
    for(int i=0;i<numV;i++){
        arrayV[i] = new int[numV]{};
    }
    while(flag==1){
        int n,m;
        cout<<"请输入要连接的两个顶点的编号:";
        cin>>n>>m;
        if(n==m) flag=0;
        else{
            arrayV[n][m]=1;
        }
    }
    displayAdjacencyMatrix(arrayV,numV);
    cout<<"邻接矩阵生成完毕！连通分量如下:"<<endl;
    for(int i=0;i<numV;i++){
        if(arrayFlag[i]==false){
            color++;
            cout<<endl;
            cout<<i<<" ";
            arrayFlag[i]=true;
            arrayColor[i]=color;
            dfsAdjacencyMatrix(arrayV,i,arrayFlag,numV,arrayColor, color);
        }
    }
    cout<<endl;
    cout<<"连通分量的染色情况如下："<<endl;
    for(int i=0;i<numV;i++) cout<<arrayColor[i]<<" ";
}

bool dfsAdjacencyMatrix(int **arrayV,int r,bool arrayFlag[],int num,int arrayColor[],int color){
//    if(arrayV[r][c]==0||arrayFlag[c]==true) return false;
//    if(arrayV[r][c]==1){
//        arrayFlag[c]=true;
//        arrayColor[c]=color;
//        cout<<c<<" ";
//        for(int i=0;i<num;i++){
//            dfsAdjacencyMatrix(arrayV,c,i,arrayFlag,num,arrayColor,color);
//        }
//    }
    for(int c=0;c<num;c++){
        if(arrayV[r][c]==1&&arrayFlag[c]==false){
            arrayFlag[c]=true;
            arrayColor[c]=color;
            cout<<c<<" ";
            dfsAdjacencyMatrix(arrayV,c,arrayFlag,num,arrayColor,color);
        }
    }
}

void displayAdjacencyMatrix(int **arrayV,int length){
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            cout<<arrayV[i][j]<<" ";
        }
        cout<<endl;
    }
}