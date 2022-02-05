#include <iostream>
#include<vector>
using namespace std;

void combinations(int set,int at,int r,int n,vector<int>&subsets); //combinations函数会生成长度为n,r个1的二进制数的全排列，比如r=3,n=4会得到{0111(7),1011(11),1101(13),1110(14)}这4个二进制数
void solve(int graph[][4],int **memo,int S,int N);
int findMinCost(int graph[][4],int **memo,int S,int N);
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
    solve(graph,memo,S,N);
    int minCost= findMinCost(graph,memo,S,N);
    cout<<minCost;
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

void solve(int graph[][4],int **memo,int S,int N){
    for(int r=3;r<=N;r++){
        vector<int>subset;
        combinations(0,0,3,4,subset);
        vector<int>::iterator it;
        for(it=subset.begin();it!=subset.end();it++){
            int sub=*it;
            if(notIn(S,sub)) continue;
            for(int next=0;next<N;next++){
                if(next==S|| notIn(next,sub)) continue;
                int state=sub^(1<<next);
                int minDist=9999;
                for(int e=0;e<N;e++){
                    if(e==S||e==next|| notIn(e,sub)) continue;
                    int newDistance=memo[e][state]+graph[e][next];
                    if(newDistance<minDist) minDist=newDistance;
                    memo[next][sub]=minDist;
                }
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

bool notIn(int i,int subset){
    if(((1<<i)&subset)==0) return true;
    else return false;
}