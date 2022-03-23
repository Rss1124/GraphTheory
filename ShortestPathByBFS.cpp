#include <iostream>
#include <queue>
using namespace std;

void adjacencyMatrix();
void bfsAdjacencyMatrix(int **arrayFlag,string graph[][7],queue<int> qR,queue<int> qC);

int main(){
    adjacencyMatrix();
}

void adjacencyMatrix(){
    int sr=0,sc=0; //S的位置
    int r=5,c=7;
    int **arrayFlag; //用来记录图中结点被访问的情况以及路径长度
    arrayFlag = new int*[r];
    for(int i=0;i<c;i++){
        arrayFlag[i] = new int[c]{};
    }
    arrayFlag[0][0]=1;
    string graph[5][7]={
                        {"S",".",".","#",".",".","."},
                        {".","#",".",".",".","#","."},
                        {".","#",".",".",".",".","."},
                        {".",".","#","#",".",".","."},
                        {"#",".","#","E",".","#","."}
                        };
    queue<int> qR; //用于存储行变化的队列
    queue<int> qC; //用于存储列变化的队列
    qR.push(sr);
    qC.push(sc);
    bfsAdjacencyMatrix(arrayFlag,graph,qR,qC);
}

void bfsAdjacencyMatrix(int **arrayFlag,string graph[][7],queue<int> qR,queue<int> qC){
    /**
     *  dR,dC为方向数组
     *  用来表示图中结点的运动方向（→，←，↓，↑）
     */
    int dR[4]={0,0,1,-1};
    int dC[4]={1,-1,0,0};
    while(qR.empty()!=true){
        int r=qR.front();
        int c=qC.front();
        qR.pop();
        qC.pop();
        for(int i=0;i<4;i++){ //0<=r<=4 0<=c<=6 r={0,0,1,-1} c={1,-1,0,0}
            int rr=r+dR[i];
            int cc=c+dC[i];
            if((0<=rr&&rr<=4)&&(0<=cc&&cc<=6)) {
                if(graph[rr][cc]=="E"){ //case1:找到终点
                    arrayFlag[rr][cc]=arrayFlag[r][c]+1;
                    cout<<arrayFlag[rr][cc];
                    break;
                }
                if(graph[rr][cc]=="."&&arrayFlag[rr][cc]==0){ //case2:有路可走
                    qR.push(rr);
                    qC.push(cc);
                    /** 路径长度+1 **/
                    arrayFlag[rr][cc]=arrayFlag[r][c]+1;
                }
            }
        }
    }
}