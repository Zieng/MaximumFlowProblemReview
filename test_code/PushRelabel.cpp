/*

time = O(VE) 

*/

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>

using namespace std;


#define MAX_SIZE 100000

// int  adj[MAX_SIZE][MAX_SIZE];         // adjacency matrix
// int  d[MAX_SIZE],  water[MAX_SIZE];        //高度、含水点的含水量
// int  *queue, *qf , *qb ;    //存放图上所有除源点和汇点外的含水点
// int V = MAX_SIZE;

int ** adj;
int *d, *water;
int *queue, *qf, *qb;
int V = MAX_SIZE;
 
void  preflow( int s , int t)
{
    for( int  j = 0 ;  j < V ; ++ j )
        if( adj[s][j] &&  j != s )
        {
            adj[j][s] +=( water[j] =  adj[s][j]);
            adj[s][j] =  0;
            if( j !=  s  &&  j  !=  t )
                *(qb++) =  j ;
        }
}
 
void  push( int  i ,  int  j )
{
    // 水量要足，且不得超过剩余容量。
    int  f  =  min( water[i],  adj[i][j]);
    water[i] -=  f ;  
    water[j] +=  f ;
    adj[i][j] -= f;  
    adj[j][i] += f;
}
 
void  relabel( int  i )
{
    for( int  j = 0 ;  j < V ; ++ j )
        if( adj[i][j])
            d[i] =  min( d[i],  d[j]);
    d[i]++;
}
 
int  preflow_push_relabel( int  s ,  int  t )
{
    qf  =  qb  =  queue ;
    d[s] =  V  -  1 ;   //设定源点高度，避免水太早灌回源点。
    preflow( s, t );
 
    while( qf  <  qb )  //除源点汇点外还有含水点就继续
    {
        int  i  = *(qf++);
        relabel( i );  //不一定能成功抬高此点，但无妨。
 
        for( int  j = 0 ;  j < V ; ++ j )
            if( d[i] ==  d[j] +  1  &&  adj[i][j] )
            {
                if( !water[j] &&  j != s  &&  j != t ) 
                    *(qb++) =  j ;
                push( i ,  j );
                if(! water[i] )
                    break ;
            }
 
        if( water[i] )
            *(qb++) =  i ;
    }
    return  water[t];
}

int main()
{
    adj = (int **) malloc( sizeof(int*)* MAX_SIZE );
    for (int i = 0; i < MAX_SIZE; ++i)
        adj[i] = (int *) malloc( sizeof(int) * MAX_SIZE );
    d = (int *) malloc( sizeof(int) * MAX_SIZE );
    water = (int *) malloc( sizeof(int) * MAX_SIZE );
    queue = (int *) malloc( sizeof(int) * (MAX_SIZE*MAX_SIZE) );
    memset( d ,  0 ,  sizeof( MAX_SIZE ));
    memset( water ,  0 ,  sizeof( MAX_SIZE ));

    time_t startTime, endTime;
    struct timeval tp;


    // input vertices number
    cin>>V;

    if (V > MAX_SIZE -1 )
    {
        cout<<"Too many vertices!!"<<endl;
        return -1;
    }

    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            cin>>adj[i][j];
        }
    }

    // default: source is 0, target is V-1
    cout<<"PushAndRelabel:"<<endl;
    
    gettimeofday(&tp, NULL);
    startTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    long maxFlow = preflow_push_relabel(0,V-1);
    gettimeofday(&tp, NULL);
    endTime = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    cout<<"\t["<< endTime-startTime <<"ms]"<<maxFlow<<endl;

    free(adj);
    free(d);
    free(water);
    free(queue);
    return 0;
}