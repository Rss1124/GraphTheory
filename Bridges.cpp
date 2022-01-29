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
bool dfsLabel(Array arrayV[],int num,int &value,int arrayLow[],int arrayID[],int pre,bool inCycle[]); //(����ͼ&&����ͼ)�ڽӱ��DFS
void findBridge(Array arrayV[],int length,int arrayLow[],int arrayID[],bool inCycle[],bool isArt[]);

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
    bool *inCycle;
    inCycle=new bool[numV]{};
    int *arrayLow;
    arrayLow=new int[numV]{};
    int *arrayID;
    arrayID=new int[numV]{};
    bool *isArt;
    isArt=new bool[numV]{};
    int value=0;
    for(int i=0;i<numV;i++){
        dfsLabel(arrayV,i,value,arrayLow,arrayID,0,inCycle);
    }
    for(int i=0;i<numV;i++) cout<<arrayID[i]<<" ";
    cout<<endl;
    for(int i=0;i<numV;i++) cout<<arrayLow[i]<<" ";
    cout<<endl;
    for(int i=0;i<numV;i++) cout<<inCycle[i]<<" ";
    cout<<endl;
    cout<<"����������:"<<endl;
    findBridge(arrayV,numV,arrayLow,arrayID,inCycle,isArt);
    cout<<"����������:"<<endl;
    for(int i=0;i<numV;i++){
        if(isArt[i]==1) cout<<i<<" ";
    }
}

bool dfsLabel(Array arrayV[],int num,int &value,int arrayLow[],int arrayID[],int pre,bool inCycle[]){ //num=0 pre=2
    if(arrayV[num].flag==true){ //case1:���ʵ��������ʵĶ��㡱��ID[num]��ID[pre]С
        if(arrayLow[num]<arrayLow[pre]){
            arrayLow[pre]=arrayLow[num];
            inCycle[num]=true;
            inCycle[pre]=true;
        }
    }
    if(arrayV[num].flag==false){
        arrayID[num]=value;
        arrayLow[num]=arrayID[num];
        value++;
        arrayV[num].flag=true;
        for(int i=0;i<arrayV[num].length;i++){
            if(arrayV[num].arrayE[i]!=pre){ //��ֹ����ͼ��������������� 3->2 2->3
                dfsLabel(arrayV,arrayV[num].arrayE[i],value,arrayLow,arrayID,num,inCycle);
                if(arrayLow[arrayV[num].arrayE[i]]<arrayLow[num]){
                    arrayLow[num]=arrayLow[arrayV[num].arrayE[i]];
                    inCycle[num]=true;
                    inCycle[arrayV[num].arrayE[i]]=true;
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

void findBridge(Array arrayV[],int length,int arrayLow[],int arrayID[],bool inCycle[],bool isArt[]){
    for(int i=0;i<length;i++){
        int count=0;
        for(int j=0;j<arrayV[i].length;j++){
            if(arrayID[i]<arrayLow[arrayV[i].arrayE[j]]){
                cout<<i<<"-"<<arrayV[i].arrayE[j]<<endl;
            }
            if(arrayLow[i]!=arrayLow[arrayV[i].arrayE[j]]){
                count++;
                if(inCycle[i]==1) isArt[i]=1;
                else if(count>1) isArt[i]=1;
            }
        }
    }
}