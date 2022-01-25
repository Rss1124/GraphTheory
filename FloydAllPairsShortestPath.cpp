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
    int graph[7][7]={
            {0,12,9999,9999,9999,16,14},
            {12,0,10,9999,9999,7,9999},
            {9999,10,9999,3,5,6,9999},
            {9999,9999,3,9999,4,9999,9999},
            {9999,9999,5,4,9999,2,8},
            {16,7,6,9999,2,9999,9},
            {14,9999,9999,9999,8,9,9999}
    };
    int next[7][7]={
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
                    graph[i][j]=graph[i][k]+graph[k][j];
                    next[i][j]=k;
                }
            }
        }
    }
}