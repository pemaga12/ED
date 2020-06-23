#include <iostream>
#include <algorithm> // swap, abs

using namespace std;


/* 

   BackTraking problem, Assigning roads to trailers...

   Solution : V[0..M)  of [0..N)
   Implicit retrictions... 
       \forall i : 0 <= i < M : frec(V,V[i])== 1 and WoR(V[i])>=WoT[i])
   Optimal solution on g = sum i : 0 <= i < N : C[i][sol[i]]

*/
   

#define MAX 10000

int M ; // Trailers
int N ; // Roads.
int WoT[MAX] ; // Width of Trailers
int WoR[MAX] ; // Width of Roads
int Q[MAX][MAX] ; // Quality of machine  - road.

bool feasible(const int sol[], const int k, const bool USED[])
{
  if (WoR[sol[k]]<WoT[k])return false;
  if (USED[sol[k]]) return false;
  return true;
}


void backTrack(int sol[], int k, int &quality,
	       int &optQuality,int optSol[],
	       bool USED[])
{
  for(int n=0; n<N; n++)
    {
      sol[k]=n;
      if (feasible(sol,k,USED))
	{
	  USED[n]=true;
	  quality += Q[k][sol[k]];
	  if (k==(M-1))
	    {
	      optQuality = max(quality,optQuality);
	      if (optQuality==quality)
		for(int m=0;m<M;m++)
		  optSol[m]=sol[m];
	    }
	  else
	    backTrack(sol,k+1,quality,optQuality, optSol,USED);
	  USED[n]=false;
	  quality -= Q[k][sol[k]];			  
	}
      
    }
}



// IO staff
int main(int argc, char *args[])
{
  int c,C ;
  bool USED[MAX];  // To mark roads...
  int k ;
  int quality, optQuality;
  int sol[MAX];
  int optSol[MAX];

  cin >> C ;
  for (c=0; c<C; c++)
    {
      cin >> M >> N ;
      for (int m=0 ; m<M ; m++) cin >> WoT[m];
      for (int n=0 ; n<N ; n++) cin >> WoR[n];
      for (int m=0 ; m<M ; m++)
	for (int n=0 ; n<N ; n++) cin >> Q[m][n];
      for (int n=0 ; n<N ; n++) USED[n]=false;
      k=quality = optQuality = 0 ;
      backTrack(sol,k,quality,optQuality, optSol, USED);
      cout << optQuality << endl;
    }
  return 0;
}
