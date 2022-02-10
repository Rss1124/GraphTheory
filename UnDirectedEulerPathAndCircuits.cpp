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

void undirectedGraph();
void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE,int arrayDegree[]); //�����ڽӱ�ͱ߱�
void findBegin(int &begin,int arrayDegree[],int numV); //��ŷ����·�������յ�
void findEulerPath(int index,int arrayDegree[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE,int pre);
void displayAdjacencyList(Array arrayV[],int length);
bool checkNext(vector<Edge>&arrayE,int begin,int next);

int main(){
    undirectedGraph();
}

void undirectedGraph(){
    vector<Edge>arrayE;
    Array arrayV[255];
    int numV;
    int numE;
    cout<<"���붥������Լ��ߵĸ���:";
    cin>>numV>>numE;
    int temp=numE;
    int *arrayDegree;
    int *tourV;
    arrayDegree=new int[numV]{};
    tourV=new int[numE+1]{};
    createAdjacencyListAndEdgeList(numV,arrayV,arrayE,arrayDegree);
    int begin=-1;
    cout<<endl;
    findBegin(begin,arrayDegree,numV);
    findEulerPath(begin,arrayDegree,arrayV,arrayE,tourV,numE,-1);
    cout<<"ŷ��·������:"<<endl;
    for(int i=0;i<=temp;i++) cout<<tourV[i]<<" ";
}

void createAdjacencyListAndEdgeList(int numV,Array arrayV[],vector<Edge>&arrayE,int arrayDegree[]){
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
            arrayDegree[i]++;
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
    for(int i=0;i<numV;i++) cout<<arrayDegree[i]<<" ";
}

void findBegin(int &begin,int arrayDegree[],int numV){
    int flag=0;
    for(int i=0;i<numV;i++){
        if(arrayDegree[i]%2!=0){
            begin=i;
            flag++;
        }
    }
    if(flag==0){
        cout<<"��ŷ����·"<<endl;
    }
    if(flag==2){
        cout<<"��ŷ��·��,���Ϊ:"<<begin<<endl;
    }
    else cout<<"ʲô��û��"<<endl;
}

void findEulerPath(int index,int arrayDegree[],Array arrayV[],vector<Edge>&arrayE,int tourV[],int &numE,int pre){ //index=0 pre=1
    for(int i=0;i<arrayV[index].length;i++){
        int next=arrayV[index].arrayE[i];
        if(checkNext(arrayE,index,next)==true&&next!=pre){
            /**
             * ע�⣬����ͼ����һ����ʱ�����index���յ�next�Ķȶ�Ҫ-1���������ڽӱ���Ҫ���ظ��ı��ų�������3->0��0->3��next==pre��
             */
            arrayDegree[index]--;
            arrayDegree[next]--;
            findEulerPath(next,arrayDegree,arrayV,arrayE,tourV,numE,index);
        }
        if(checkNext(arrayE,index,next)==false) continue;
    }
    if(arrayDegree[index]==0){
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
