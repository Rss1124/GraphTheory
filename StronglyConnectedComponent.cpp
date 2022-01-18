#include <iostream>
#include <stack>

using namespace std;

/** �ڽӱ� **/
typedef struct Array{
    int arrayE[255];
    int length=0;
}Array;

void displayAdjacencyList(Array arrayV[],int length);
void adjacencyList();
bool dfsAdjacencyList(Array arrayV[],int num,bool arrayFlag[],bool arrayIsStack[],stack<int> &s,int arrayColor[]); //(����ͼ&&����ͼ)�ڽӱ���DFS
void displayAdjacencyMatrix(int **arrayV,int length);
void adjacencyMatrix();
bool dfsAdjacencyMatrix(int **arrayV,int r,int c,bool arrayFlag[],int num); //(����ͼ&&����ͼ)�ڽӾ����DFS

int main() {
//    adjacencyList();
    adjacencyMatrix();
}

void adjacencyList(){
    Array arrayV[255];
    bool *arrayFlag;
    bool *arrayIsStack;
    int *arrayColor;
    stack<int> stackV;
    int numV;
    cout<<"���붥�����:";
    cin>>numV;
    arrayFlag=new bool[numV]{};
    arrayIsStack=new bool[numV]{};
    arrayColor=new int[numV]{};
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
    cout<<"�ڽӱ�������ϣ�Ⱦɫ������£�"<<endl;
    for(int i=0;i<numV;i++){
        dfsAdjacencyList(arrayV,i,arrayFlag,arrayIsStack,stackV,arrayColor);
    }
    for(int i=0;i<numV;i++) cout<<arrayColor[i];
}

bool dfsAdjacencyList(Array arrayV[],int num,bool arrayFlag[],bool arrayIsStack[],stack<int> &s,int arrayColor[]){
    if(arrayFlag[num]==true&&arrayIsStack[num]==true) return true; //case1:�ý���Ѿ������ʹ��ˣ��ҽ����ջ��
    if(arrayFlag[num]==true&&arrayIsStack[num]==false) return false; //case2:�ý���Ѿ������ʹ��ˣ��ҽ�㲻��ջ��

    arrayColor[num]=num;
    s.push(num);
    arrayIsStack[num]=true;

    if(arrayFlag[num]==false&&arrayV[num].length==0){ //case3:��·����
        s.pop();
        arrayFlag[num]=true;
        arrayIsStack[num]=false;
        return false;
    }
    if(arrayFlag[num]==false&&arrayV[num].length!=0){ //case4:��·����
        arrayFlag[num]=true;
        for(int i=0;i<arrayV[num].length;i++){
            dfsAdjacencyList(arrayV,arrayV[num].arrayE[i],arrayFlag,arrayIsStack,s,arrayColor);
            if(arrayIsStack[arrayV[num].arrayE[i]]==true){
                if(arrayColor[arrayV[num].arrayE[i]]<arrayColor[num]) arrayColor[num]=arrayColor[arrayV[num].arrayE[i]];
            }
        }
    }
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
    cout<<"���붥�����:";
    cin>>numV;
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
    cout<<"�ڽӾ���������ϣ�"<<endl;
    for(int i=0;i<numV;i++){
        if(arrayFlag[i]==false){
            cout<<i<<" ";
            arrayFlag[i]=true;
        }
        for(int j=0;j<numV;j++){
            if(i!=j) dfsAdjacencyMatrix(arrayV,i,j,arrayFlag,numV);
        }
    }
}

bool dfsAdjacencyMatrix(int **arrayV,int r,int c,bool arrayFlag[],int num){
    if(arrayV[r][c]==0||arrayFlag[c]==true) return false;
    if(arrayV[r][c]==1){
        arrayFlag[c]=true;
        cout<<c<<" ";
        for(int i=0;i<num;i++){
            dfsAdjacencyMatrix(arrayV,c,i,arrayFlag,num);
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