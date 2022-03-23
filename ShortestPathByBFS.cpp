#include <iostream>
#include <queue>
using namespace std;

void adjacencyMatrix();
void bfsAdjacencyMatrix(int **arrayFlag,string graph[][7],queue<int> qR,queue<int> qC);

int main(){
    adjacencyMatrix();
}

void adjacencyMatrix(){
    int sr=0,sc=0; //S��λ��
    int r=5,c=7;
    int **arrayFlag; //������¼ͼ�н�㱻���ʵ�����Լ�·������
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
    queue<int> qR; //���ڴ洢�б仯�Ķ���
    queue<int> qC; //���ڴ洢�б仯�Ķ���
    qR.push(sr);
    qC.push(sc);
    bfsAdjacencyMatrix(arrayFlag,graph,qR,qC);
}

void bfsAdjacencyMatrix(int **arrayFlag,string graph[][7],queue<int> qR,queue<int> qC){
    /**
     *  dR,dCΪ��������
     *  ������ʾͼ�н����˶����򣨡���������������
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
                if(graph[rr][cc]=="E"){ //case1:�ҵ��յ�
                    arrayFlag[rr][cc]=arrayFlag[r][c]+1;
                    cout<<arrayFlag[rr][cc];
                    break;
                }
                if(graph[rr][cc]=="."&&arrayFlag[rr][cc]==0){ //case2:��·����
                    qR.push(rr);
                    qC.push(cc);
                    /** ·������+1 **/
                    arrayFlag[rr][cc]=arrayFlag[r][c]+1;
                }
            }
        }
    }
}