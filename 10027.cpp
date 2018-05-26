/*
   NOIP2009最优贸易
   分析：spfa
        (1)关键是维护什么域
            mmin:当前结点之前的最小的商品买入价格
            f:当前最大利润
        (2)动态方程
            f[e[t].to] = max(f[i]        ,w[e[t].to]  -    mmin[i]       )
            终点最大利润     始点最大利润 终点价值  始点及之前点最小买入价格
 */
#include <iostream>
#include <cstdio>
#include <queue>
#include <climits>
using namespace std;
const int N=100001;
const int M=1000001;
const int INF=INT_MIN;
struct zk { 
    int from;     //起点
    int  to;      //终点
    int next;     //相同起点的下一条边
};  
zk e[M];     //存边
int coutEdge=0;    //边数，又作边数组e中的位置  
int n,m;
int w[N];        //顶点的权值，不是边的权值
int first[N];    //邻接表的起始位置
queue<int> q;  
int f[N],mmin[N];  
bool used[N];
void add(int a,int b)
{
    coutEdge++;         //下一条边的位置
    e[coutEdge].from=a; e[coutEdge].to=b;
    e[coutEdge].next=first[a]; first[a]=coutEdge;
    return;
}
void read()
{
    int i,a,b,c;
    scanf("%d%d",&n,&m);        //读入顶点和边数
    for (i=1;i<=n;i++)
        scanf("%d",&w[i]);      //每个城市的商品价格
    for (i=1;i<=n;i++)
    { 
        mmin[i]=w[i];           //当前结点之前的最小商品买入价格
        f[i]=INF;               //到当前结点所能获得的最大利润
    }
    for (i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        add(a,b);   if (c==2)  add(b,a);  //准备边,注意双向边
    }
    return;
}
void spfa()
{
    int i,t;   bool flag;
    while(!q.empty()) q.pop();
    q.push(1); used[1]=1; f[1]=0;
    while(!q.empty())
    {
        i=q.front(); t=first[i];    //找到队首顶点为始点的邻接表起始位置
        while(t!=0)                 //遍历从该点出去的所有边
        {
            flag=0;
            if (f[e[t].to]<max(f[i],w[e[t].to]-mmin[i]))
            {
                f[e[t].to]=max(f[i],w[e[t].to]-mmin[i]);
                flag=1;
            }
            if (mmin[e[t].to]>mmin[i])
            {
                mmin[e[t].to]=mmin[i];
                flag=1;
            }
            if (flag&&!used[e[t].to])
            {
                q.push(e[t].to);
                used[e[t].to]=1;
            }
            t=e[t].next;
        }
        q.pop();  used[i]=0;
    }
    printf("%d",f[n]);
    return;
}
int main()
{
    freopen("input.txt","r",stdin);
    // freopen("trade.out","w",stdout); 
    read();
    spfa();
    return 0;
}
