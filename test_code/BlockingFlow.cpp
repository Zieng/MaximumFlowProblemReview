/*

time = O(V^2 * E) 

*/


#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <sys/time.h>

using namespace std;

#define MAX_SIZE 100000

int adj[MAX_SIZE]; // adjacency lists，初始化為-1。

struct Element
{
    int vertexId, capacity, next;
} e[MAX_SIZE];

int  shortest[MAX_SIZE];      // 最短距離
bool  visit[MAX_SIZE];       // BFS/DFS visit record
int  queue[MAX_SIZE];       // queue


// int *adj; // adjacency lists，初始化為-1。

// struct Element
// {
//     int vertexId, capacity, next;
// } *e;

// int  *shortest;      // 最短距離
// bool *visit;       // BFS/DFS visit record
// int  *queue;       // queue


long long ElementId = 0;

// add edge (a,b) with capacity c
void addedge(int a, int b, int c)
{
    if( a==b )
        return;
    e[ElementId] = (Element) { b, c, adj[a] };
    adj[a] = ElementId++;

    e[ElementId] = (Element) { a, 0, adj[b] };
    adj[b] = ElementId++;
}


int BFS(int s, int t)
{
    // cout<<"BFS::start"<<endl;
    // memset(shortest, 0x7f, MAX_SIZE*sizeof(int) );
    // memset(visit, false, MAX_SIZE*sizeof(int) );
    memset(shortest, 0x7f, sizeof(shortest) );
    memset(visit, false, sizeof(visit) );

    int qn = 0;
    shortest[s] = 0;
    visit[s] = true;
    queue[qn++] = s;

    // for (int i = 0; i <= t; ++i)
    // {
    //     cout<<"visit["<<i<<"]="<<visit[i]<<endl;
    // }

    for (int qf=0; qf<qn; ++qf)
    {
        int a = queue[qf];
        // cout<<"BFS::vertex="<<a<<endl;

        for (int i = adj[a]; i != -1; i = e[i].next )
        {
            int b = e[i].vertexId;
            int cap = e[i].capacity;

            // cout<<"Element["<<i<<"]:\tvertexId="<<b<<",capacity="<<cap<<endl;

            if ( e[i].capacity > 0 && !visit[b] )
            {
                // cout<<"enqueue"<<endl;
                shortest[b] = shortest[a] + 1;
                visit[b] = true;
                queue[qn++] = b;
                if (b == t)
                    return shortest[t];
            }
        }
    }
    // cout<<"BFS::end"<<endl;
    return MAX_SIZE;
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
    if (a == t)
        return df;

    if (visit[a])
        return 0;
    visit[a] = true;

    for (int i = adj[a]; i != -1; i = e[i].next)
    {
        int b = e[i].vertexId;
        if ( e[i].capacity > 0 && shortest[a] + 1 == shortest[b])
        {
            int f = DFS(b, min(df, e[i].capacity), s, t);
            if (f)
            {
                e[i].capacity -= f;
                e[i^1].capacity += f;
                return f;
            }
        }
    }
    return 0;
}

int dinic(int s, int t)
{
    int flow = 0;
    while ( BFS(s, t) < MAX_SIZE )
    {
        while (true)
        {
            // memset(visit, false, MAX_SIZE*sizeof(bool));
            memset(visit, false, sizeof(visit));
            int f = DFS(s, 1e9, s, t);
            if (!f) 
                break;
            flow += f;
        }
    }
    return flow;
}

int main()
{
    // adj = (int *) malloc( sizeof(int) * MAX_SIZE );
    // e = (struct Element *) malloc( sizeof(struct Element) * (MAX_SIZE<<2));
    // shortest = (int *) malloc( sizeof(int) * MAX_SIZE );
    // visit = (bool *) malloc( sizeof(bool) * MAX_SIZE );
    // queue = (int *) malloc( sizeof(int) * MAX_SIZE );
    // memset(adj,-1,MAX_SIZE*sizeof(int));

    memset(adj,-1,sizeof(adj));

	int capacity,verticesNumber;
    struct timeval tp;
    long startTime,endTime;

    

    cin>>verticesNumber;
    for (int i = 0; i < verticesNumber; ++i)
    {
        for (int j = 0; j < verticesNumber; ++j)
        {
            cin>>capacity;
            addedge(i,j,capacity);
        }
    }

    cout<<"BlockingFlow:"<<endl;
    gettimeofday(&tp, NULL);
    startTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    long maxFlow = dinic(0,verticesNumber-1);
    gettimeofday(&tp, NULL);
    endTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    cout<<"\t["<<endTime-startTime<<"ms]"<<maxFlow<<endl;

    // free(adj);
    // free(e);
    // free(shortest);
    // free(visit);
    // free(queue);

	return 0;
}