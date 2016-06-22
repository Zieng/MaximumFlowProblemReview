/*
time = O(V * E^2)
*/


#include <iostream>
#include <queue>
#include <sys/time.h>
using namespace std;
#define MAX_SIZE 100000

int adj[MAX_SIZE][MAX_SIZE];    // adjacency matrix
int q[MAX_SIZE], *qf, *qb;    // BFS queue
int p[MAX_SIZE];              // BFS tree
 
int Edmonds_Karp(int s, int t, int N)
{
    int f = 0;     
    while (true)   
    {
        memset(p, -1, sizeof(p) );
        qf = qb = q;
        p[*qb++ = s] = s;
        while (qf < qb && p[t] == -1)
            for (int i = *qf++, j = 0; j < N; ++j)
                if (p[j] == -1 && adj[i][j])
                    p[*qb++ = j] = i;
        if (p[t] == -1) break;
        int df = 1e9;
        for (int i = p[t], j = t; i != j; i = p[j = i])
            df = min(df, adj[i][j]);
        for (int i = p[t], j = t; i != j; i = p[j = i])
            adj[i][j] -= df, adj[j][i] += df;
        f += df;
    }
    return f;
}


int main()
{
    int n, s, t;
    struct timeval tp;
    long startTime,endTime;

    cin >> n;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            cin >> adj[i][j];
        }
    }
    cin >> s >> t;

    cout<<"Edmonds_Karp:"<<endl;
    gettimeofday(&tp, NULL);
    startTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    int maxFlow = Edmonds_Karp(0, n-1, n);
    gettimeofday(&tp, NULL);
    endTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    cout<<"\t["<<endTime-startTime<<"ms]"<<maxFlow<<endl;
}

