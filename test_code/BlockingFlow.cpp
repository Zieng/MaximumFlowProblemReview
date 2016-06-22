#include <stdio.h>
#include <memory.h>

#define MAX_SIZE (2048)


const int V = MAX_SIZE, E = MAX_SIZE<<1;
 
int adj[V]; // adjacency lists，初始化為-1。
struct Element
{
    int b, r, next;
} e[E*2];

int en = 0;
 
void addedge(int a, int b, int c)
{
    e[en] = (Element) { b, c, adj[a] };
    adj[a] = en++;
    e[en] = (Element) { a, 0, adj[b] };
    adj[a] = en++;
}
 
int d[V];       // 最短距離
bool visit[V];  // BFS/DFS visit record
int q[V];       // queue
 
// 計算最短路徑，求出容許網路。
int BFS(int s, int t)
{
    memset(d, 0x7f, sizeof(d));
    memset(visit, false, sizeof(visit));
 
    int qn = 0;
    d[s] = 0;
    visit[s] = true;
    q[qn++] = s;
 
    for (int qf=0; qf<qn; ++qf)
    {
        int a = q[qf];
        for (int i = adj[a]; i != -1; i = e[i].next)
        {
            int b = e[i].b;
            if (e[i].r > 0 && !visit[b])
            {
                d[b] = d[a] + 1;
                visit[b] = true;
                q[qn++] = b;
                if (b == t) return d[t];
            }
        }
    }
    return V;
}
 
int min(int a, int b){
    if(a>b)
        return b;
    else
        return a;
}

// 求出一條最短擴充路徑，並擴充流量。
int DFS(int a, int df, int s, int t)
{
    if (a == t) return df;
 
    if (visit[a]) return 0;
    visit[a] = true;
 
    for (int i = adj[a]; i != -1; i = e[i].next)
    {
        int b = e[i].b;
        if (e[i].r > 0 && d[a] + 1 == d[b])
        {
            int f = DFS(b, min(df, e[i].r), s, t);
            if (f)
            {
                e[i].r -= f;
                e[i^1].r += f;
                return f;
            }
        }
    }
    return 0;
}
 
int dinic(int s, int t)
{
    int flow = 0;
    while (BFS(s, t) < V)
        while (true)
        {
            memset(visit, false, sizeof(visit));
            int f = DFS(s, 1e9, s, t);
            if (!f) break;
            flow += f;
        }
    return flow;
}

int main(){
	int path,i,node;
	int source,target,capacity;
	int flow;

	scanf("%d\n",&node);
    for (int i = 0; i < node; ++i)
    {
        for (int j = 0; j < node; ++j)
        {
            
        }
    }

	// scanf("%d\n",&path);
	// for(i=0;i<path;i++){
	// 	scanf("%d %d %d",&source,&target,&capacity);
	// 	addedge(source,target,capacity);
	// }
	flow=dinic(0,node-1);
	printf("maximum flow is: %d\n",flow);
	return 0;
}