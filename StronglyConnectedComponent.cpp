#include <iostream>
#include <stack>

using namespace std;

/** 邻接表 **/
typedef struct Array{
    int arrayE[255];
    int length=0;
}Array;

void displayAdjacencyList(Array arrayV[],int length);
void adjacencyList();
bool dfsAdjacencyList(Array arrayV[],int num,bool arrayFlag[],bool arrayIsStack[],stack<int> &s,int arrayColor[]); //(有向图&&无向图)邻接表的DFS
void displayAdjacencyMatrix(int **arrayV,int length);
void adjacencyMatrix();
bool dfsAdjacencyMatrix(int **arrayV,int r,bool arrayFlag[],int num,bool arrayIsStack[],stack<int> &s,int arrayColor[]); //(有向图&&无向图)邻接矩阵的DFS

int main() {
    adjacencyList(); //邻接表下的Trajan算法找寻有向图的强连通分量
//    adjacencyMatrix(); //邻接矩阵下的Trajan算法找寻有向图的强连通分量
}

void adjacencyList(){
    Array arrayV[255];
    bool *arrayFlag;
    bool *arrayIsStack;
    int *arrayColor;
    stack<int> stackV;
    int numV;
    cout<<"输入顶点个数:";
    cin>>numV;
    arrayFlag=new bool[numV]{};
    arrayIsStack=new bool[numV]{};
    arrayColor=new int[numV]{};
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
    cout<<"邻接表生成完毕！染色情况如下："<<endl;
    for(int i=0;i<numV;i++){
        dfsAdjacencyList(arrayV,i,arrayFlag,arrayIsStack,stackV,arrayColor);
    }
    for(int i=0;i<numV;i++) cout<<arrayColor[i];
}

/** tarjan算法:在回溯的时候,对顶点进行染色 **/
bool dfsAdjacencyList(Array arrayV[],int num,bool arrayFlag[],bool arrayIsStack[],stack<int> &s,int arrayColor[]){
    if(arrayFlag[num]==true) return true; //case1:该结点已经被访问过了

    arrayColor[num]=num;
    s.push(num);
    arrayIsStack[num]=true;

    if(arrayFlag[num]==false&&arrayV[num].length==0){ //case2:无路可走
        s.pop();
        arrayFlag[num]=true;
        arrayIsStack[num]=false;
        return false;
    }
    if(arrayFlag[num]==false&&arrayV[num].length!=0){ //case3:有路可走
        arrayFlag[num]=true;
        for(int i=0;i<arrayV[num].length;i++){
            dfsAdjacencyList(arrayV,arrayV[num].arrayE[i],arrayFlag,arrayIsStack,s,arrayColor);

            /** 如果结点在栈中,那么对其进行染色 **/
            if(arrayIsStack[arrayV[num].arrayE[i]]==true){
                if(arrayColor[arrayV[num].arrayE[i]]<arrayColor[num]) arrayColor[num]=arrayColor[arrayV[num].arrayE[i]];
            }
        }
    }

    /** 防止错误的染色情况 **/
    if(num==arrayColor[num]){
        while(s.top()!=num){
            arrayIsStack[s.top()]=false;
            s.pop();
        }
        if(s.top()==num) {
            arrayIsStack[s.top()]=false;
            s.pop();
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
    bool *arrayIsStack;
    stack<int> stackV;
    int *arrayColor;
    cout<<"输入顶点个数:";
    cin>>numV;
    arrayFlag = new bool[numV]{};
    arrayV = new int*[numV];
    arrayIsStack = new bool[numV]{};
    arrayColor = new int[numV]{};
    for(int i=0;i<numV;i++){
        arrayV[i] = new int[numV]{};
    }
    while(flag==1){
        int n,m;
        cout<<"请输入要连接的两个顶点的编号(输入两个相同的编号就会结束输入):";
        cin>>n>>m;
        if(n==m) flag=0;
        else{
            arrayV[n][m]=1;
        }
    }
    displayAdjacencyMatrix(arrayV,numV);
    cout<<"邻接矩阵生成完毕！染色情况如下:"<<endl;
    for(int i=0;i<numV;i++){
        if(arrayFlag[i]==false){
            arrayFlag[i]=true;
            arrayColor[i]=i;
            stackV.push(i);
            arrayIsStack[i]=true;
            dfsAdjacencyMatrix(arrayV,i,arrayFlag,numV,arrayIsStack,stackV,arrayColor);
        }
    }
    for(int i=0;i<numV;i++) cout<<arrayColor[i];
}

bool dfsAdjacencyMatrix(int **arrayV,int r,bool arrayFlag[],int num,bool arrayIsStack[],stack<int> &s,int arrayColor[]){
    for(int c=0;c<num;c++){
        if(arrayV[r][c]==1&&arrayFlag[c]==false){ //case1:有路可走
            arrayFlag[c]=true;
            arrayColor[c]=c;
            s.push(c);
            arrayIsStack[c]=true;
            dfsAdjacencyMatrix(arrayV,c,arrayFlag,num,arrayIsStack,s,arrayColor); //c=2
        }
        if(arrayV[r][c]==1&&arrayFlag[c]==true){
            if(arrayIsStack[c]==true){ //case2:顶点c已经遍历过了，并且c在栈中
                if(arrayColor[c]<arrayColor[r]) arrayColor[r]=arrayColor[c]; //染色
            }
            //case3:顶点c已经遍历过了，并且c不在栈中
        }
    }

    /** 防止错误的染色 **/
    if(r==arrayColor[r]){
        while(s.top()!=r){
            arrayIsStack[s.top()]=false;
            s.pop();
        }
        if(s.top()==r) {
            arrayIsStack[s.top()]=false;
            s.pop();
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