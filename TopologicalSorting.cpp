#include <iostream>

using namespace std;

/** �ڽӱ� **/
typedef struct Array{
    int arrayE[255];
    int length=0;
    bool flag=false;
}Array;

void displayAdjacencyList(Array arrayV[],int length);
void adjacencyList();
bool dfsAdjacencyList(Array arrayV[],int num,int arrayTs[],int &index); //(����ͼ&&����ͼ)�ڽӱ���DFS
void displayAdjacencyMatrix(int **arrayV,int length);
void adjacencyMatrix();
bool dfsAdjacencyMatrix(int **arrayV,int r,bool arrayFlag[],int num,int arrayTs[],int &index); //(����ͼ&&����ͼ)�ڽӾ����DFS

int main() {
//    adjacencyList();
    adjacencyMatrix();
}

void adjacencyList(){
    Array arrayV[255];
    int *arrayTS;
    int numV,index;
    cout<<"���붥�����:";
    cin>>numV;
    index=numV;
    arrayTS=new int[numV];
    for(int i=0;i<numV;i++){
        int numE;
        cout<<"�������"<<i<<"�Ŷ��������Ķ������:";
        cin>>numE;
        for(int j=0;j<numE;j++){
            int v;
            cout<<"�������"<<i<<"�Ŷ��������ľ��嶥��ı��:";
            cin>>v;
            arrayV[i].arrayE[j]=v;
            arrayV[i].length++;
            cout<<"��"<<i<<"�Ŷ������"<<v<<"�Ŷ���ɹ�����"<<endl;
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"�ڽӱ�������ϣ�������������:"<<endl;
    for(int i=0;i<numV;i++){
        dfsAdjacencyList(arrayV,i,arrayTS,index);
    }
    for(int i=0;i<numV;i++){
        cout<<arrayTS[i]<<" ";
    }
}

bool dfsAdjacencyList(Array arrayV[],int num,int arrayTs[],int &index){
    if(arrayV[num].flag==true){
        return false;
    }
    if(arrayV[num].flag==false){
        arrayV[num].flag=true;
        for(int i=0;i<arrayV[num].length;i++){
            dfsAdjacencyList(arrayV,arrayV[num].arrayE[i],arrayTs,index);
        }
        arrayTs[--index]=num; //�ݹ����ʱ�����Ӧ�ĵ���Եõ�����������
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
    int *arrayTS;
    int numV,index;
    int **arrayV;
    int flag=1;
    bool *arrayFlag;
    cout<<"���붥�����:";
    cin>>numV;
    index=numV;
    arrayTS=new int[numV];
    arrayFlag = new bool[numV]{};
    arrayV = new int*[numV];
    for(int i=0;i<numV;i++){
        arrayV[i] = new int[numV]{};
    }
    while(flag==1){
        int n,m;
        cout<<"������Ҫ���ӵ���������ı��:";
        cin>>n>>m;
        if(n==m) flag=0;
        else{
            arrayV[n][m]=1;
        }
    }
    displayAdjacencyMatrix(arrayV,numV);
    cout<<"�ڽӾ���������ϣ������������£�"<<endl;
    for(int i=0;i<numV;i++){
        if(arrayFlag[i]==false){
            arrayFlag[i]=true;
            dfsAdjacencyMatrix(arrayV,i,arrayFlag,numV,arrayTS,index);
        }
    }
    for(int i=0;i<numV;i++){
        cout<<arrayTS[i]<<" ";
    }
}

bool dfsAdjacencyMatrix(int **arrayV,int r,bool arrayFlag[],int num,int arrayTs[],int &index){
    for(int c=0;c<num;c++){
        if(arrayV[r][c]==1&&arrayFlag[c]==false){
            arrayFlag[c]=true;
            dfsAdjacencyMatrix(arrayV,c,arrayFlag,num,arrayTs,index);
        }
    }
    arrayTs[--index]=r; //�ݹ����ʱ�����Ӧ�ĵ���Եõ�����������
}

void displayAdjacencyMatrix(int **arrayV,int length){
    for(int i=0;i<length;i++){
        for(int j=0;j<length;j++){
            cout<<arrayV[i][j]<<" ";
        }
        cout<<endl;
    }
}