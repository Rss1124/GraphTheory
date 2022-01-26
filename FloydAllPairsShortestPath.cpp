#include <iostream>
#include <queue>
using namespace std;

void adjacencyMatrix();
void floyd(int graph[][7],int numV,int next[][7]);

int main(){
    adjacencyMatrix();
}

void adjacencyMatrix(){
    int numV=7;
    int graph[7][7]={ //距离矩阵
            {0,2,5,9999,9999,9999,10},
            {9999,0,2,9999,11,9999,9999},
            {9999,9999,0,9999,9999,9999,2},
            {9999,9999,9999,0,9999,9999,9999},
            {9999,9999,9999,9999,0,1,9999},
            {9999,9999,9999,9999,-2,0,9999},
            {9999,9999,9999,9999,9999,11,0}
    };
    int next[7][7]={ //路径矩阵
            {0,1,2,3,4,5,6},
            {0,1,2,3,4,5,6},
            {0,1,2,3,4,5,6},
            {0,1,2,3,4,5,6},
            {0,1,2,3,4,5,6},
            {0,1,2,3,4,5,6},
            {0,1,2,3,4,5,6}
    };
    floyd(graph,numV,next);
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            cout<<next[i][j]<<" ";
        }
        cout<<endl;
    }
}

void floyd(int graph[][7],int numV,int next[][7]){
    for(int k=0;k<numV;k++){
        for(int i=0;i<numV;i++){
            for(int j=0;j<numV;j++){
                if(i!=j&&i!=k&&j!=k&&graph[i][j]>graph[i][k]+graph[k][j]){
                    if(graph[i][k]+graph[k][j]>1000) graph[i][j]=9999; //＋∞ ± 任何数 = ＋∞
                        /** 如果i->k->j的距离比i->j短，更新距离矩阵和路径矩阵 **/
                    else graph[i][j]=graph[i][k]+graph[k][j];
                    next[i][j]=k;
                }
            }
        }
    }
    for(int k=0;k<numV;k++){
        for(int i=0;i<numV;i++){
            for(int j=0;j<numV;j++){
                if(i!=j&&i!=k&&j!=k&&graph[i][j]>graph[i][k]+graph[k][j]){
                    /** 出现负回路的几种情况
                     * 正 + 正 < 正
                     * 正 + 负 < 正
                     * 负 + 正 < 正
                     * －∞ + 负 < 正
                     * 负 + －∞ < 正
                    **/
                    if(graph[i][k]>0&&graph[k][j]>0) graph[i][j]=-9999,next[i][j]=-1;
                    if(graph[i][k]>0&&graph[k][j]<0&&graph[k][j]!=-9999) graph[i][j]=-9999,next[i][j]=-1;
                    if(graph[i][k]<0&&graph[i][k]!=-9999&&graph[k][j]>0) graph[i][j]=-9999,next[i][j]=-1;
                    if(graph[i][k]==-9999&&(graph[k][j]<0&&graph[k][j]!=-9999)) graph[i][j]=-9999,next[i][j]=-1;
                    if((graph[i][k]<0&&graph[i][k]!=-9999)&&graph[k][j]==-9999) graph[i][j]=-9999,next[i][j]=-1;
                }
            }
        }
    }
}