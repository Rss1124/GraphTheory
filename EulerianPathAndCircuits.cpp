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

void createAdjacencyListAndEdgeList(int numV,Array array[],vector<Edge>&arrayE,int arrayIn[],int arrayOut[]); //�����ڽӱ�ͱ߱�
void findBeginAndEnd(int &begin,int &end,int arrayIn[],int arrayOut[],int numV); //��ŷ����·�������յ�
void displayAdjacencyList(Array arrayV[],int length);

int main(){
    vector<Edge>arrayE;
    Array arrayV[255];
    int numV;
    int numE;
    cout<<"���붥������Լ��ߵĸ���:";
    cin>>numV>>numE;
    int *arrayIn;
    int *arrayOut;
    arrayIn=new int[numV]{};
    arrayOut=new int[numV]{};
    createAdjacencyListAndEdgeList(numV,arrayV,arrayE,arrayIn,arrayOut);
    int begin=-1;
    int end=-1;
    findBeginAndEnd(begin,end,arrayIn,arrayOut,numV);
}

void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE,int arrayIn[],int arrayOut[]){
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
            arrayOut[i]++;
            arrayIn[v]++;
            cout<<"��"<<i<<"�Ŷ������"<<v<<"�Ŷ���ɹ�����"<<endl;
            Edge e;
            e.begin=i;
            e.end=v;
            arrayE.push_back(e);
        }
    }
    displayAdjacencyList(arrayV,numV);
    cout<<"�ڽӱ�������ϣ�"<<endl;
    vector<Edge>::iterator it;
    for(it=arrayE.begin();it!=arrayE.end();it++){
        cout<<it->begin<<"->"<<it->end<<endl;
    }
    cout<<"�߱��������"<<endl;
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
        cout<<"��ŷ����·"<<endl;
    }
    if(beginState==1&&endState==1){
        cout<<"��ŷ��·��,���Ϊ:"<<begin<<",�յ�Ϊ:"<<end<<endl;
    }
    if(beginState==-1&&endState==-1) cout<<"û��ŷ��·��"<<endl;
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


