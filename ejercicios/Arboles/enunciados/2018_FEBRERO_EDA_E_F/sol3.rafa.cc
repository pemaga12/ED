#include <iostream>

using namespace std;

// Those variables are constants per case, so we can
// declare them as "globals"...

int R,A,B,m; // (R)olos, (A)ctors, (B)udget, (m)inimum

#define MAX 10000

int SALARY[MAX] ;
int AFFINITY[MAX][MAX] ; // Role,Actor


int feasible(const int sol[],const int r, const int a, const int b, const int marked[])
{
  if (marked[r]) return 0;
  if (AFFINITY[r][a]<m) return 0;
  if ((b+SALARY[a])>B) return 0;
  return 1;
}

// (r)ole, (b)udget (af)inity(local) (AF)initty(transient opt)
void maxCast(int sol[],const int r,const int b,const int af,
	     int marked[],
	     int &AF,int &BU,int opt[])
{
  for(int a=0; a < A ; a++)
    {
      if (feasible(sol,r,a,b,marked))
	{
	  sol[r]=a;
	  if ((r+1) == R) // valid
	    {
	      if (af+AFFINITY[r][a] > AF)
		{
		  AF=af+AFFINITY[r][a];
		  BU = b + SALARY[a];
		  for(int rr=0; rr<R; rr++) opt[rr]=sol[rr];
		}
	    }
	  else
	    {
	      marked[r]=1;
	      maxCast(sol,r+1,b+SALARY[a],af+AFFINITY[r][a] ,marked,AF,BU,opt);
	      marked[r]=0;	      
	    }
	}
    }
}

int main(int argc, char *args[])
{
  int marked[MAX];
  int sol[MAX], opt[MAX];
  int BU,AF;
  // Entry Protocol : (2 + n) lines
  for (cin >> R >> A >> B >> m ; R || A || B || m  ;cin >> R >> A >> B >> m)
    {
      for (int a=0 ;a <A ; a++)
	{
	  marked[a]= 0 ;
	  cin >> SALARY[a];
	}
      for (int r=0 ; r<R ; r++)
	for (int a=0 ; a <A ; a++) cin >> AFFINITY[r][a];
      BU=0;
      AF=-1;
      maxCast(sol,0,0,0,marked,AF,BU,opt);
      cout << AF << " " << BU << endl;
      for (int r=0 ; r<R ; r++)
	cout << r << " " << opt[r] << endl;
    }
}

/*

g++ sol3.rafa.cc -o main && ./main

2 3 200 4
100 100 100
10 5 0
0 5 10

20 200
0 0
1 2

3 5 100 40
50 20 40 30 40
100 0 70 50 60 
0 50 40 30 60
0 60 50 70 40

220 100
0 0
1 1
2 3
*/
