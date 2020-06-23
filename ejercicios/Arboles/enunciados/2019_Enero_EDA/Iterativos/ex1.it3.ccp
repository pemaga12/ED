/*

  Longest segment having all consecutive numbers


  P : N >= 0
  Q : res = max i,j : 0 <= i <= j <= N and AllesCons(V,i,j)  : j-i

  where
     AllesCons(V,i,j) = \forall p : i <= p < j-1 : |V[p]-V[p+1]|=1  * 

     * Mind j-1 !


  I : Q[N/n] and  min(1,N) <=  n <= N and
      left = min i : 0 <= i <= n and AllesCons(V,i,n) : i

  !B : n == N || N-left < res   * (local optimization, not required)

   B : (n < N && N-left >= res)


   C(N,n) = N - n >= 0 

  
  I and B |- Q  (Trivial with n==N.
                 With N-left<res no new maximum can be computed.
                 Therefore Q[N/n] -> Q)

Invariant snapshot:
-------------------

0           left=2           n=N-1   N
+-----+-----+-----+-----+-----+-----+
|  0  |  2  |  4  |  5  |   6 | 7   |
+-----+-----+-----+-----+-----+-----+
            -------res = 3 ---



  Init:
  -----
     n,left, res = min(1,N), 0, min(1,N)
     
  P |- I[n/min(1,N),left/0,res/min(1,N)]  (Trivial)


  Step:
  -----
     n = n + 1 , Clearly quota decreases!


  Restore:
  --------
    case n+1 == N or |V[n]-V[n+1]| = 1
          res = max(res,n+1-left)
    e.o.c
          left = n + 1 

   (Proof not required)
   I and B |- (n+1 == N or |V[n]-V[n+1]| = 1) -> I[n/n+1][res/max(res,n+1-left)] 
   I and B |- (n<N and |V[n]-V[n+1]|!= 1) -> I[n/n+1][left/n+1]


 O(N) since loop executes in O(N) times in worst case, and body and guard are O(1),
  hence O(N*1)
*/
#include <iostream>
#include <algorithm>

using namespace std;


#define MAX 100000

int solve(const int V[], const int N)
{
  int n,left, res;
  for(res=n=min(N,1), left = 0 ; n<N && (N-left >= res); n++)
    if ((n+1 == N) || (abs(V[n]-V[n+1]) == 1))
      res= max(res,n+1-left);
    else
      left = n + 1 ;
  return res;
}


int main(int argc, char *args[])
{
  int C;
  int n,N;
  cin >> C ;
  int V[MAX];
  for(int c=0 ; c < C ; c++)
    {
      cin >> N;
      for(int n=0 ; n < N ; n++) cin >> V[n];
      cout << solve(V,N) << endl;
    }
 return 0;
}

           





