/*
 * Longest Subsequence of General Fibonacci series
 *
 * author : Rafael Martinez Torres
 *
 * P : V[0..N) N >= 0
 * Q : res = max p,q : 0 <= p <= q <= N && AllesFib(V,p,q) : q - p
 *
 *
 * where
 * AllesFib(V,p,q) = \forall i : p+2 <= i < q : V[i]=V[i-1]+V[i-2]
 *
 0                 n                                          N
 +-----+-----+-----+-----+-...-+-----+-----+-----+-----+-----+
 |  -1 |  6  |  5  |  10 |     |     |     |     |     |     |
 +-----+-----+-----+-----+-...-+-----+-----+-----+-----+-----+
 * I : 0 <= n <= N &&
 *     Q[N/n]
 *
 * B : n < N
 * ---
 *
 * Init
 * ----
 * n , res = min(N,1), min(N,1)
 * 
 * Step : n = n + (t-n)
 * ----
 *      where t = max p : n-1 <= p < N && AllesFib(V,n-1,p):p  wow! (**)
 *
 *      (**) which is equivalent to
 *      
 *      t = max p : n+1 <= p < N && AllesSum(V,n+1,p): p 
 *
 *      where AllesSum(V,n,p) = \forall i : n <= i < p : V[n]=V[n-1]+V[n-2]
 *
 *   Quota(n) = N - n >= 0
 *   --------
 *          In worst case n=n+(t-n), t >= n + 1, hence it decreases.
 *
 *   Restore:
 *   --------
 *
 *   if (t - (n-1)) > res
 *       res = (t - (n-1))   wow!
 *
 *   where t = max p : n-1 <= p < N && AllesFib(V,n-1,p):p 
 *
 *
 *   Pseudocode:
 *   -----------
 *   n , res = min(N,1), min(N,1)
 *   while (n < N)
 *      // 1 <= n < N   wow!
 *      t = n +1
 *      while (t < N ) && (V[t]=V[t-1]+V[t-2])
 *          t = t + 1
 *      if (t - (n-1)) > res
 *          res = (t - (n-1))
 *      n = n + (t - n);
 *   done
 *
 *   Complexity, is O(N) .
 *   Due to inner loop, it is safe
 *   to claim O(N*N), but inaccurate.
 *   The critical instruction is executed
 *   an _absolute_ number of (N-1) times
 *   and so the loop guard (t < N) is
 *   executed an _absolute_ number of
 *   N  times, hence O(N)
 *
 */

// C/C++ flavour style.
#include <iostream>  // cin, cout
#include <algorithm>  // min, max

using namespace std;

int longestGenFibSubSeq(const int V[], const int N)
{
  int res, n,t;
  for (n=res=min(N,1); n < N ; n=t)
    {
      for (t=n+1 ; (n < N) && (V[t]==(V[t-1] + V[t-2]));t++);
      res=max(res,t-(n-1));
    }
  return res;
}

#define MAX 10000
int main(int argc, char **args)
{
  int N;
  int V[MAX];
  for( ; cin >> N ; )
    {
      for(int n=0;n<N;n++) cin >> V[n];
      cout << longestGenFibSubSeq(V,N) << endl;
    }
}
