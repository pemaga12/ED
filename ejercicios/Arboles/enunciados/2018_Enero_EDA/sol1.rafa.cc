/*

  Longest track subsequence in Sky  by Yolanda Ortega

  Sol by Rafael Martinez Torres


  P : N >= 0
  Q : M = max p,q : 0 <= p <= q <= N and AllesStr(V,p,q,>=) : q - p    *

  where AllesStr(V,p,q,>=) ::= \forall i : p <= i < q-1 : V[i] >= V[i+1]

  * [] is empty subsequence of tracks, hence max length is 0.

*/

#define MAX 100000

#include <iostream> // cin, cout
#include <algorithm> // max

using namespace std;

/* See full development and derivation below */
int solve(const int V[], const int N)
{
  int n,MM,M ;
  for (n=min(N,0),M=MM=(N>0);n < N ; n++ )
    {
      MM = (V[n-1]>=V[n])*MM + 1;
      M =  max(MM,M);
    }
  return M;
}


int main(int argc, char *args[])
{
  int C,c;
  int N ;
  int V[MAX];
  cin >> C;
  for (int c=0; c<C ; c++)
    {
      cin >> N;
      for(int n=0; n<N; n++) cin >> V[n];
      cout << solve(V,N) << endl;
    }
  return 0;
}



/*


  Possible invariants:

0                                         n                 N
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
|  1  |   3 |  2  |  1  |  2  |  2  |  2  |  2  |     |     |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
      M = MM = 3       





  I : Q[N/n] and min(N,1) <= n <= N
      M' = max p : 0 <= p <= n and AllesStr(V,p,n,>=) :  n - p 
 
      M' for efficiency.

     
  B : n < N 


  Init:
  -----

     n,M,M' = min(N,0),\chi(N>0),\chi(N>0)


  Step:
  -----
     n = n + 1


  Quote:
  -------
    C(n) = N - n  >= 0 (since I)

  
  Restore:
  --------

  case V[n] <= V[n-1] :
    M' = M' + 1
  eoc
    M' = 1
  esac
  M = max (M,M');

(i.e., 
     M' = \chi(V[n]<= V[n-1])*M' + 1 
     M  = max(M,M')
*/

/*

 TODO. Long step.

0                                         n                 N
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
|  1  |   3 |  2  |  1  |  2  |  2  |  2  |  6  |     |     |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
      M = 3       

*/
	
