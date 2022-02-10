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

void directedGraph();
void createAdjacencyListAndEdgeList(int numV,Array array[],vector<Edge>&arrayE,int arrayIn[],int arrayOut[]); //�����ڽӱ�ͱ߱�
void findBeginAndEnd(int &begin,int &end,int arrayIn[],int arrayOut[],int numV); //��ŷ����·�������յ�
void findEulerPath(int index,int arrayOut[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE);
void displayAdjacencyList(Array arrayV[],int length);
bool checkNext(vector<Edge>&arrayE,int begin,int next);

int main(){
    directedGraph();
}

void directedGraph(){
    vector<Edge>arrayE;
    Array arrayV[255];
    int numV;
    int numE;
    cout<<"���붥������Լ��ߵĸ���:";
    cin>>numV>>numE;
    int temp=numE;
    int *arrayIn;
    int *arrayOut;
    int *tourV;
    arrayIn=new int[numV]{};
    arrayOut=new int[numV]{};
    tourV=new int[numE+1]{};
    createAdjacencyListAndEdgeList(numV,arrayV,arrayE,arrayIn,arrayOut);
    int begin=-1;
    int end=-1;
    findBeginAndEnd(begin,end,arrayIn,arrayOut,numV);
    findEulerPath(begin,arrayOut,arrayV,arrayE,tourV,numE);
    cout<<"ŷ��·������:"<<endl;
    for(int i=0;i<=temp;i++) cout<<tourV[i]<<" ";
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

void findEulerPath(int index,int arrayOut[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE){ //index=1
    for(int i=0;i<arrayV[index].length;i++){
        int next=arrayV[index].arrayE[i];
        if(checkNext(arrayE,index,next)==true){
            arrayOut[index]--;
            findEulerPath(next,arrayOut,arrayV,arrayE,tourV,numE);
        }
        if(checkNext(arrayE,index,next)==false) continue;
    }
    if(arrayOut[index]==0){
        tourV[numE--]=index;
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

bool checkNext(vector<Edge>&arrayE,int begin,int next){
    vector<Edge>::iterator it;
    for(it=arrayE.begin();it!=arrayE.end();it++){
        if(it->begin==begin&&it->end==next){
            if(it->visited==false){
                it->visited=true;
                return true; //begin->next������û�����ʹ�,��������Ϊ�ѷ���
            }
        }
    }
    return false;
}

