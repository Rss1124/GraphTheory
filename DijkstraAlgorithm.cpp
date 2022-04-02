#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

typedef struct Node{
    int v;
    int w;
}Node;

typedef struct Array{
    Node arrayE[255];
    int length=0;
    bool flag=false;
}Array;

void adjacencyMatrix();
void displayAdjacencyMatrix(int **arrayV,int length);
void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<int> &q,int c,int arrayDist[]);
void adjacencyList();
void displayAdjacencyList(Array arrayV[],int length);
void bfsAdjacencyList(Array arrayV[],queue<int> &q,int arrayDist[],int prev[]);
void findPath(int prev[],int end,int numV);

int main(){
    adjacencyList();
//    adjacencyMatrix();
}

void adjacencyMatrix(){

    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

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

    QueryPerformanceCounter(&nBeginTime);
    bfsAdjacencyMatrix(arrayV,arrayFlag,queue_List,numV,arrayDist);
    QueryPerformanceCounter(&nEndTime);

    for(int i=0;i<numV;i++) cout<<arrayDist[i]<<" ";
    cout<<endl;
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"����ʱ��:"<<time*1000<<"ms";
}

void bfsAdjacencyMatrix(int **arrayV,bool arrayFlag[],queue<int> &q,int c,int arrayDist[]){
    while(q.empty()!=true){
        int temp=q.front();
        q.pop();
        int s=-1;
        int min=9999;
        for(int i=0;i<c;i++){
            if(temp!=i&&arrayV[temp][i]!=0&&arrayFlag[i]==false){
                if(arrayDist[temp]+arrayV[temp][i]<arrayDist[i]){
                    arrayDist[i]=arrayDist[temp]+arrayV[temp][i]; //����dist����

                    if(arrayDist[i]<min){
                        min=arrayDist[i];
                        s=i;
                    }
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

void adjacencyList(){
    double time=0;
    LARGE_INTEGER nFreq;
    LARGE_INTEGER nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&nFreq);

    queue<int> queue_List;
    int s=0;
    int *arrayDist;
    int *arrayMemo;
    int *prev;
    Array arrayV[255];
    int numV;
    cout<<"���붥�����:";
    cin>>numV;
    arrayDist = new int[numV]{};
    arrayMemo = new int[numV]{};
    prev = new int[numV]{};
    arrayMemo[s]=1<<s;
    for(int i=0;i<numV;i++){
        arrayDist[i]=9999; //��ʼ��dist����Ϊ9999
    }
    arrayDist[s]=0;
    for(int i=0;i<numV;i++){
        int numE;
        cout<<"�������"<<i<<"�Ŷ��������Ķ������:";
        cin>>numE;
        for(int j=0;j<numE;j++){
            int v;
            int w;
            cout<<"�������"<<i<<"�Ŷ��������ľ��嶥��ı�������:";
            cin>>v>>w;
            arrayV[i].arrayE[j].v=v;
            arrayV[i].arrayE[j].w=w;
            arrayV[i].length++;
            cout<<"��"<<i<<"�Ŷ������"<<v<<"�Ŷ���ɹ�"<<endl;
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"�ڽӱ�������ϣ�"<<endl;

    QueryPerformanceCounter(&nBeginTime);
    for(int i=0;i<numV;i++){
        if(arrayV[i].flag==false){
            queue_List.push(i);
            arrayV[i].flag=true;
            bfsAdjacencyList(arrayV,queue_List,arrayDist,prev);
        }
    }
    QueryPerformanceCounter(&nEndTime);

    for(int i=0;i<numV;i++) cout<<arrayDist[i]<<" ";
    cout<<endl;
    time=(double)(nEndTime.QuadPart-nBeginTime.QuadPart)/(double)nFreq.QuadPart;
    cout<<"����ʱ��:"<<time*1000<<"ms"<<endl;
    cout<<"prev��������:"<<endl;
    for(int i=0;i<numV;i++) cout<<prev[i]<<" "; //prev����:ÿ�������ǰ������
    cout<<"���·������:"<<endl;
    for(int e=0;e<numV;e++){
        if(e==s) continue;
        cout<<s<<"->"<<e<<":";
        findPath(prev,e,numV);
        cout<<endl;
    }
}

void bfsAdjacencyList(Array arrayV[],queue<int> &q,int arrayDist[],int prev[]){
    while(q.empty()==false){
        int temp=q.front();
        q.pop();
        int s=-1;
        int min=9999;
        if(arrayV[temp].length!=0){
            for(int i=0;i<arrayV[temp].length;i++){
                if(arrayV[arrayV[temp].arrayE[i].v].flag==false){
                    if(arrayDist[temp]+arrayV[temp].arrayE[i].w<arrayDist[arrayV[temp].arrayE[i].v]){
                        arrayDist[arrayV[temp].arrayE[i].v]=arrayDist[temp]+arrayV[temp].arrayE[i].w;
                        prev[arrayV[temp].arrayE[i].v]=temp;
                    }
                    if(arrayDist[arrayV[temp].arrayE[i].v]<min){
                        min=arrayDist[arrayV[temp].arrayE[i].v];
                        s=arrayV[temp].arrayE[i].v;
                    }
                }
            }
        }
        if(s!=-1) {
            q.push(s);
            arrayV[s].flag=true;
        }
    }
}

void displayAdjacencyList(Array arrayV[],int length){
    for(int i=0;i<length;i++){
        cout<<i;
        for(int j=0;j<arrayV[i].length;j++){
            cout<<"->("<<arrayV[i].arrayE[j].w<<")"<<arrayV[i].arrayE[j].v;
        }
        cout<<endl;
    }
}

void findPath(int prev[],int end,int numV){
    for(int i=end;i>=0&&i<numV;){
        if(i==0){
            cout<<i;
            break;
        }
        cout<<i<<"-";
        i=prev[i];
    }
}