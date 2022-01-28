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
bool dfsLabel(Array arrayV[],int num,int &value,int arrayColor[],int pre); //(����ͼ&&����ͼ)�ڽӱ��DFS
void findBridge(Array arrayV[],int length,int arrayColor[]);

int main() {
    adjacencyList();
}

void adjacencyList(){
    Array arrayV[255];
    int numV;
    cout<<"���붥�����:";
    cin>>numV;
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
    cout<<"�ڽӱ�������ϣ�Ⱦɫ�������:"<<endl;
    int *arrayColor;
    arrayColor=new int[numV]{};
    int value=0;
    for(int i=0;i<numV;i++){
        dfsLabel(arrayV,i,value,arrayColor,0);
    }
    for(int i=0;i<numV;i++) cout<<arrayColor[i]<<" ";
    cout<<endl;
    cout<<"����������:"<<endl;
    findBridge(arrayV,numV,arrayColor);
}

bool dfsLabel(Array arrayV[],int num,int &value,int arrayColor[],int pre){ //num=0 pre=2
    if(arrayV[num].flag==true){ //case1:���ʵ��������ʵĶ��㡱��ID[num]��ID[pre]С
        if(arrayColor[num]<arrayColor[pre]) arrayColor[pre]=arrayColor[num];
    }
    if(arrayV[num].flag==false){
        arrayColor[num]=value++;
        arrayV[num].flag=true;
        for(int i=0;i<arrayV[num].length;i++){
            if(arrayV[num].arrayE[i]!=pre){ //��ֹ����ͼ��������������� 3->2 2->3
                dfsLabel(arrayV,arrayV[num].arrayE[i],value,arrayColor,num);
                if(arrayColor[arrayV[num].arrayE[i]]<arrayColor[num]) arrayColor[num]=arrayColor[arrayV[num].arrayE[i]];
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

void findBridge(Array arrayV[],int length,int arrayColor[]){
    for(int i=0;i<length;i++){
        for(int j=0;j<arrayV[i].length;j++){
            if(arrayColor[i]<arrayColor[arrayV[i].arrayE[j]]) cout<<i<<"-"<<arrayV[i].arrayE[j]<<endl;
        }
    }
}