#include <iostream>
#include <queue>
#include <windows.h>
using namespace std;

typedef struct Edge{
    int s;
    int e;
    int w;
}Edge;

void createEdgeArray();
void BF(int distArray[], Edge arrayE[],int numV,int numE);

int main(){
    createEdgeArray();
}

void createEdgeArray(){
    int numE,numV;
    cout<<"���붥����ߵĸ���:";
    cin>>numV>>numE;
    Edge *arrayE;
    int *distV;
    arrayE=new Edge[numE]; //�߱�
    distV=new int[numE];
    int s,e,w;
    for(int i=0;i<numV;i++){
        distV[i]=99999;
    }
    distV[0]=0;
    for(int i=0;i<numE;i++){
        cout<<"������㣬�յ��Լ����ߵľ���:";
        cin>>s>>e>>w;
        arrayE[i].s=s;
        arrayE[i].e=e;
        arrayE[i].w=w;
        cout<<"��"<<s<<"���"<<e<<"���ӳɹ�,����Ϊ:"<<w<<endl;
    }
    BF(distV,arrayE,numV,numE);
    for(int i=0;i<numV;i++){
        cout<<distV[i]<<" ";
    }
}


/**
 * ��ͼ����numV-1���ɳڲ���,�õ����п��ܵ����·��
 * @param distArray :��̾�������,���������ж������̾���,�ʼ�����������·��Ϊ0����,����ֵ����+��
 * @param arrayE :�߱�
 * @param numV :����ĸ���
 * @param numE :�ߵĸ���
 */
void BF(int distArray[], Edge arrayE[],int numV,int numE){
    for(int i=0;i<numV-1;i++){
        for(int j=0;j<numE;j++){
            if(i==0&&distArray[arrayE[j].s]+arrayE[j].w<distArray[arrayE[j].e]){
                distArray[arrayE[j].e]=distArray[arrayE[j].s]+arrayE[j].w;
            }
            if(i>0&&distArray[arrayE[j].s]+arrayE[j].w<distArray[arrayE[j].e]){
                distArray[arrayE[j].e]=-9999;
            }
        }
    }
}
