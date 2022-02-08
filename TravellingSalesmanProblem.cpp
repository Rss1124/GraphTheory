#include <iostream>
#include<vector>
using namespace std;

void combinations(int set,int at,int r,int n,vector<int>&subsets);
void setUp(int graph[][4],int **memo,int S,int N);
void solve(int graph[][4],int **memo,int S,int N);
int findMinCost(int graph[][4],int **memo,int S,int N);
void findOptimalTour(int graph[][4],int **memo,int S,int N,int tour[]);
bool notIn(int i,int subset);

int main(){
    int graph[4][4]={ //�������
            {0,1,2,4},
            {3,0,7,5},
            {6,2,0,1},
            {4,5,9,0}
    };
    int S=0;
    int N=4;
    int **memo;
    memo=new int*[100];
    for(int i=0;i<100;i++) memo[i] = new int[100]{};
    setUp(graph,memo,S,N);
    solve(graph,memo,S,N);
    int minCost= findMinCost(graph,memo,S,N);
    cout<<minCost<<endl;
    int *tour;
    tour=new int[N+1]{};
    findOptimalTour(graph,memo,S,N,tour);
    for(int i=0;i<=N;i++) cout<<tour[i]<<" ";
}

void combinations(int set,int at,int r,int n,vector<int>&subsets){
    /**
     * ͨ���ݹ�ķ���
     * combinations���������ɳ���Ϊn,r��1�Ķ���������ȫ����
     * ����r=3,n=4��õ�0111(7),1011(11),1101(13),1110(14)��4����������
     */
    if(r==0) subsets.push_back(set); //r==0ʱ���ͻ�õ�r��1�Ķ�������
    else{
        for(int i=at;i<n;i++){
            set=set | (1<<i);
            combinations(set,i+1,r-1,n,subsets);
            set=set & ~(1<<i);
        }
    }
}

void setUp(int graph[][4],int **memo,int S,int N){
    /**
    * setUpִ���Ժ�
    * memo[next][sub]: next��ʾ��һ��Ҫ���ʵĽ�㣬sub��ʾ·���ı��������1��ʾ����Ѿ������ʣ�0��ʾ���δ������
    * memo[1][3]=graph[0][1] next=1 sub=0011(3),(����0->����1��
    * memo[2][5]=graph[0][2] next=2 sub=0101(5),(����0->����2��
    * memo[3][9]=graph[0][3] next=3 sub=1001(9),(����0->����3��
    */
    for(int i=0;i<N;i++){
        if(i==S) continue;
        memo[i][1<<S|1<<i]=graph[S][i];
    }
}

void solve(int graph[][4],int **memo,int S,int N){
    for(int r=3;r<=N;r++){
        vector<int>subset;
        combinations(0,0,r,N,subset);
        vector<int>::iterator it;
        for(it=subset.begin();it!=subset.end();it++){
            int sub=*it;
            if(notIn(S,sub)==true) continue;
            for(int next=0;next<N;next++){
                if(next==S||notIn(next,sub)==true) continue;
                int state=sub^(1<<next);
                int minDist=9999;
                for(int e=0;e<N;e++){
                    if(e==S||e==next|| notIn(e,sub)==true) continue;
                    int newDistance=memo[e][state]+graph[e][next];
                    if(newDistance<minDist) minDist=newDistance;
                }
                memo[next][sub]=minDist;
                /**
                 * ��r=3ʱ����4��sub:0111(7),1011(11),1101(13),1110(14),�����ʼ�ĵ���0������1110Ҫ�ų�
                 * ��sub=0111(7)ʱ�������
                 * memo[next][sub]: next��ʾ��һ��Ҫ���ʵĽ�㣬sub��ʾ·���ı��������1��ʾ����Ѿ������ʣ�0��ʾ���δ������
                 * memo[1][7]= memo[2][5]+graph[2][1] = graph[0][2]+graph[2][1] , next=1,sub=0111(7),(����0->����2->����1)
                 * memo[2][7]= memo[1][3]+graph[1][2] = graph[0][1]+graph[1][2] , next=2,sub=0111(7),(����0->����1->����2)
                 */
            }
        }
    }
}

int findMinCost(int graph[][4],int **memo,int S,int N){
    int end_state=(1<<N)-1; //end_stateȡ���ڽ��ĸ���N�����ݶ������������ԣ�Nλ�������ܱ�ʾ�����������2^N-1,��N=4ʱ��end_state=15(1111)�����ñ�ʾÿ����㶼�����ʹ���
    int minTourCost=9999;
    for(int e=0;e<N;e++){
        if(e==S) continue;
        int tourCost=memo[e][end_state]+graph[e][S]; //graph[e][S]��ʾ���Ҫ�������S�ĵ�e��S֮��ľ���
        if(tourCost<minTourCost) minTourCost=tourCost;
    }
    return minTourCost;
}

void findOptimalTour(int graph[][4],int **memo,int S,int N,int tour[]){
    int lastIndex=S; //��ʾ�����ʵĶ��㣬���������S
    int state=(1<<N)-1; //end_state
    for(int i=N-1;i>=1;i--){
        int index=-1;
        for(int j=0;j<N;j++){ //������ÿ�������Ϊ������N+1-i�������ʵĽ��
            if(j==S|| notIn(j,state)) continue;
            if(index==-1) index=j;
            int prevDist=memo[index][state]+graph[index][lastIndex];
            int newDist=memo[j][state]+graph[j][lastIndex];
            if(newDist<prevDist) index=j; //�ҵ�������N+1-i�������ʵĽ��->������N-i��������̵Ľ�㣬���Ҹ���index
        }
        tour[i]=index; //�ҵ�������N+1-i�Ľ��󣬽���洢��tour������
        state=state^(1<<index); //����state�����統index=2��state=15ʱ��state=1111^0100=1011
        lastIndex=index; //������󱻷��ʵĵ�
    }
    tour[0]=tour[N]=S;
}

bool notIn(int i,int subset){
    if(((1<<i)&subset)==0) return true;
    else return false;
}