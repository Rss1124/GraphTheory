#include <iostream>
#include <queue>
using namespace std;

typedef struct Array{
    int arrayE[255];
    int length=0;
    bool flag=false;
}Array;

void adjacencyList();
void adjacencyMatrix();
void displayAdjacencyMatrix(int **arrayV,int length);
void displayAdjacencyList(Array arrayV[],int length);
void bfsAdjacencyList(Array arrayV[],queue<int> &q);
void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<int> &q,int c);

int main(){
//    adjacencyList();
    adjacencyMatrix();
}

void adjacencyList(){
    queue<int> queue_List;
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
    for(int i=0;i<numV;i++){
        if(arrayV[i].flag==false){
            queue_List.push(i);
            arrayV[i].flag=true;
            bfsAdjacencyList(arrayV,queue_List);
        }
    }
}

void bfsAdjacencyList(Array arrayV[],queue<int> &q){
    while(q.empty()==false){
        int temp=q.front();
        q.pop();
        cout<<temp;
        if(arrayV[temp].length!=0){
            for(int i=0;i<arrayV[temp].length;i++){
                if(arrayV[arrayV[temp].arrayE[i]].flag==false){
                    q.push(arrayV[temp].arrayE[i]);
                    arrayV[arrayV[temp].arrayE[i]].flag=true;
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

void adjacencyMatrix(){
    int numV;
    int **arrayV;
    int flag=1;
    bool *arrayFlag;
    queue<int> queue_List;
    cout<<"输入顶点个数:";
    cin>>numV;
    arrayFlag = new bool[numV]{};
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
    cout<<"邻接矩阵生成完毕！"<<endl;
    for(int i=0;i<numV;i++){
        if(arrayFlag[i]==false){
            queue_List.push(i);
            arrayFlag[i]=true;
        }
        bfsAdjacencyMatrix(arrayV,arrayFlag,queue_List,numV);
    }
}

void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<int> &q,int c){
    while(q.empty()!=true){
        int temp=q.front();
        cout<<temp<<" ";
        q.pop();
        for(int i=0;i<c;i++){
            if(temp!=i&&arrayV[temp][i]==1&&arrayFlag[i]==false){
                q.push(i);
                arrayFlag[i]=true;
            }
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