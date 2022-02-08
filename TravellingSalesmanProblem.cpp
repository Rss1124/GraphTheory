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
    for(int i=0;i<=N;i++) cout<<tour[i]<<" ";
}

void combinations(int set,int at,int r,int n,vector<int>&subsets){
    /**
     * 通过递归的方法
     * combinations函数会生成长度为n,r个1的二进制数的全排列
     * 比如r=3,n=4会得到0111(7),1011(11),1101(13),1110(14)这4个二进制数
     */
    if(r==0) subsets.push_back(set); //r==0时，就会得到r个1的二进制数
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
    * setUp执行以后
    * memo[next][sub]: next表示下一个要访问的结点，sub表示路径的遍历情况，1表示结点已经被访问，0表示结点未被访问
    * memo[1][3]=graph[0][1] next=1 sub=0011(3),(顶点0->顶点1）
    * memo[2][5]=graph[0][2] next=2 sub=0101(5),(顶点0->顶点2）
    * memo[3][9]=graph[0][3] next=3 sub=1001(9),(顶点0->顶点3）
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
                 * 当r=3时，有4种sub:0111(7),1011(11),1101(13),1110(14),但是最开始的点是0，所以1110要排除
                 * 当sub=0111(7)时的情况：
                 * memo[next][sub]: next表示下一个要访问的结点，sub表示路径的遍历情况，1表示结点已经被访问，0表示结点未被访问
                 * memo[1][7]= memo[2][5]+graph[2][1] = graph[0][2]+graph[2][1] , next=1,sub=0111(7),(顶点0->顶点2->顶点1)
                 * memo[2][7]= memo[1][3]+graph[1][2] = graph[0][1]+graph[1][2] , next=2,sub=0111(7),(顶点0->顶点1->顶点2)
                 */
            }
        }
    }
}

int findMinCost(int graph[][4],int **memo,int S,int N){
    int end_state=(1<<N)-1; //end_state取决于结点的个数N，根据二进制数的特性，N位二级制能表示的最大数就是2^N-1,当N=4时，end_state=15(1111)，正好表示每个结点都被访问过了
    int minTourCost=9999;
    for(int e=0;e<N;e++){
        if(e==S) continue;
        int tourCost=memo[e][end_state]+graph[e][S]; //graph[e][S]表示最后要返回起点S的点e和S之间的距离
        if(tourCost<minTourCost) minTourCost=tourCost;
    }
    return minTourCost;
}

void findOptimalTour(int graph[][4],int **memo,int S,int N,int tour[]){
    int lastIndex=S; //表示最后访问的顶点，首先是起点S
    int state=(1<<N)-1; //end_state
    for(int i=N-1;i>=1;i--){
        int index=-1;
        for(int j=0;j<N;j++){ //依次让每个结点作为倒数第N+1-i个被访问的结点
            if(j==S|| notIn(j,state)) continue;
            if(index==-1) index=j;
            int prevDist=memo[index][state]+graph[index][lastIndex];
            int newDist=memo[j][state]+graph[j][lastIndex];
            if(newDist<prevDist) index=j; //找到倒数第N+1-i个被访问的结点->倒数第N-i个距离最短的结点，并且更新index
        }
        tour[i]=index; //找到倒数第N+1-i的结点后，将其存储到tour数组里
        state=state^(1<<index); //更新state，比如当index=2，state=15时，state=1111^0100=1011
        lastIndex=index; //更新最后被访问的点
    }
    tour[0]=tour[N]=S;
}

bool notIn(int i,int subset){
    if(((1<<i)&subset)==0) return true;
    else return false;
}