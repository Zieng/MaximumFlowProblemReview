#include <iostream>
#include <vector>
#include <string>

using namespace std;


#define MAX_SIZE (65535)

int  adj[MAX_SIZE][MAX_SIZE];         // adjacency matrix
int  d[MAX_SIZE],  water[MAX_SIZE];        //高度、含水点的含水量
int  *queue, *qf , *qb ;    //存放图上所有除源点和汇点外的含水点
int V = MAX_SIZE - 1;
 
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
    memset( d ,  0 ,  sizeof( d ));
    memset( water ,  0 ,  sizeof( water ));
    qf  =  qb  =  queue = new int[MAX_SIZE << 1] ;
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
    delete [] queue;
    return  water[t];
}

int main()
{
    // input vertices number
    cin>>V;
    // cin>>source>>target;
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
    cout<<"pf:"<<endl;
    cout<<preflow_push_relabel(0, V-1)<<endl;

    return 0;
}