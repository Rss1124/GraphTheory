#include <iostream>
#include<vector>
using namespace std;

void combinations(int set,int at,int r,int n,vector<int>&subsets); //combinations函数会生成长度为n,r个1的二进制数的全排列，比如r=3,n=4会得到{0111(7),1011(11),1101(13),1110(14)}这4个二进制数
void setUp(int graph[][4],int **memo,int S,int N);
void solve(int graph[][4],int **memo,int S,int N);
int findMinCost(int graph[][4],int **memo,int S,int N);
void findOptimalTour(int graph[][4],int **memo,int S,int N,int tour[]);
bool notIn(int i,int subset);

int main(){
    int graph[4][4]={ //距离矩阵
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
    for(int i=0;i<N;i++) cout<<tour[i]<<" ";
}

void combinations(int set,int at,int r,int n,vector<int>&subsets){
    if(r==0) subsets.push_back(set); //r==0时，刚好是n位二进制数
    else{
        for(int i=at;i<n;i++){
            set=set | (1<<i);
            combinations(set,i+1,r-1,n,subsets);
            set=set & ~(1<<i);
        }
    }
}

void setUp(int graph[][4],int **memo,int S,int N){
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
            }
        }
    }
}

int findMinCost(int graph[][4],int **memo,int S,int N){
    int end_state=(1<<N)-1;
    int minTourCost=9999;
    for(int e=0;e<N;e++){
        if(e==S) continue;
        int tourCost=memo[e][end_state]+graph[e][S];
        if(tourCost<minTourCost) minTourCost=tourCost;
    }
    return minTourCost;
}

void findOptimalTour(int graph[][4],int **memo,int S,int N,int tour[]){
    int lastIndex=S;
    int state=(1<<N)-1;
    for(int i=N-1;i>=1;i--){
        int index=-1;
        for(int j=0;j<N;j++){
            if(j==S|| notIn(j,state)) continue;
            if(index==-1) index=j;
            int prevDist=memo[index][state]+graph[index][lastIndex];
            int newDist=memo[j][state]+graph[j][lastIndex];
            if(newDist<prevDist) index=j;
        }
        tour[i]=index;
        state=state^(1<<index);
        lastIndex=index;
    }
    tour[0]=tour[N]=S;
}

bool notIn(int i,int subset){
    if(((1<<i)&subset)==0) return true;
    else return false;
}