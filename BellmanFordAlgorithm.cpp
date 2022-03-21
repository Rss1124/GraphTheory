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
    cout<<"输入顶点与边的个数:";
    cin>>numV>>numE;
    Edge *arrayE;
    int *distV;
    arrayE=new Edge[numE]; //边表
    distV=new int[numE];
    int s,e,w;
    for(int i=0;i<numV;i++){
        distV[i]=99999;
    }
    distV[0]=0;
    for(int i=0;i<numE;i++){
        cout<<"输入起点，终点以及两者的距离:";
        cin>>s>>e>>w;
        arrayE[i].s=s;
        arrayE[i].e=e;
        arrayE[i].w=w;
        cout<<"点"<<s<<"与点"<<e<<"连接成功,距离为:"<<w<<endl;
    }
    BF(distV,arrayE,numV,numE);
    for(int i=0;i<numV;i++){
        cout<<distV[i]<<" ";
    }
}


/**
 * 对图进行numV-1次松弛操作,得到所有可能的最短路径
 * @param distArray :最短距离数组,包含了所有顶点的最短距离,最开始除了起点的最短路径为0以外,其他值都是+∞
 * @param arrayE :边表
 * @param numV :顶点的个数
 * @param numE :边的个数
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
