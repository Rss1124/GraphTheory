#include <iostream>
#include <queue>
using namespace std;

void adjacencyMatrix();
void displayAdjacencyMatrix(int **arrayV,int length);
//void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<Node> &q,int c,int arrayDist[]);
void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<int> &q,int c,int arrayDist[]);

int main(){
    adjacencyMatrix();
}

void adjacencyMatrix(){
    int numV;
    cout<<"���붥�����:";
    cin>>numV;
    int s=0;
    int **arrayV;
    int *arrayDist;
    int flag=1;
    bool *arrayFlag;
    queue<int> queue_List;
    arrayFlag = new bool[numV]{};
    arrayV = new int*[numV];
    arrayDist = new int[numV]{};
    for(int i=0;i<numV;i++){
        arrayDist[i]=9999; //��ʼ��dist����Ϊ9999
        arrayV[i] = new int[numV]{};
    }
    arrayDist[s]=0;
    while(flag==1){
        int n,m,w;
        cout<<"������Ҫ���ӵ���������ı��,�Լ����ߵľ���:";
        cin>>n>>m>>w;
        if(n==m) flag=0;
        else{
            arrayV[n][m]=w;
        }
    }
    displayAdjacencyMatrix(arrayV,numV);
    cout<<"�ڽӾ���������ϣ�"<<endl;
    queue_List.push(s);
    arrayFlag[s]=true;
    bfsAdjacencyMatrix(arrayV,arrayFlag,queue_List,numV,arrayDist);
    for(int i=0;i<numV;i++) cout<<arrayDist[i]<<" ";
}

void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<int> &q,int c,int arrayDist[]){
    while(q.empty()!=true){
        int temp=q.front();
        q.pop();
        for(int i=0;i<c;i++){
            if(temp!=i&&arrayV[temp][i]!=0&&arrayFlag[i]==false){
               if(arrayDist[temp]+arrayV[temp][i]<arrayDist[i]){
                   arrayDist[i]=arrayDist[temp]+arrayV[temp][i]; //����dist����
               }
            }
        }
        int s=-1;
        int min=9999;
        for(int i=0;i<c;i++){
            if(arrayFlag[i]==false){
                if(arrayDist[i]<min){
                    min=arrayDist[i];
                    s=i;
                }
            }
        }
        if(s!=-1) {
            q.push(s);
            arrayFlag[s]=true;
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