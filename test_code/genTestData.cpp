#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <stdio.h>

using namespace std;

#define MAX_CAPACITY 64

int main()
{
	int numVertices, source, target;
	srand( (unsigned)time(NULL) );
	cin>>numVertices;
	cout<<numVertices<<endl;
	
	// source = rand()%numVertices;
	// target = source;
	// while( target == source )
	// 	target = rand()%numVertices;
	// cout<<source<<" "<<target<<endl;

	for (int i = 0; i < numVertices; ++i)
	{
		for (int j = 0; j < numVertices; ++j)
		{
			if (j!=numVertices-1)
				cout<< rand()%MAX_CAPACITY <<" ";
			else
				cout<< rand()%MAX_CAPACITY <<endl;
			
		}
	}
}