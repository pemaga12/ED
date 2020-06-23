/*
  Spec: (Hard)

  P : N >=0 and K > 0
  Q : r = min i,j : 0 <= i <= j <= N+1 and ((j-i)<=N -> K=count(V,i,j,N+0)):j-i   *
      where

         count(V,i,j,N) ::= #p: i <= p < min(N,j) : V[p]=1

    Informally, the minimum length (j-i) of a segment holding K number of items '1'
    If no segment, then (j-i)=N+1 is return (v.g with 0, you always get 1)

	 * N+0 (pedantic on purpose to make feasible syntactic replacement for I)


Invariant snapshot
------------------
k=5,c=4

0           m                                         n     N
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-...-+
|  0  |  0  |  1  |  0  |  1  |  0  |  0  |  1  |  1  |     |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-...-+

  I : Q[N+0/n] and 0 <= m <= n <= N+0 and 0 <= c <= k and
      c = #p : m<=p<n : V[p]=1

  !B : n=N+0 || N-n < k - c (still Can be tunned, worst case inaltered)

  B : n==N and N-n >= k-c   


  C(N,m,n) = 2N -m -n >= 0

(Informally, V[m..n) allocates a band whose number of items are not
 greater than K and r holds partial result for Q[N/n].
 c is added for efficiency reasons, and algorithm advance by step
 either n or m)

  I and !B |- Q  (Not trivial)


Init:
-----
   n,m,c,r = 0,0,0,N+1  

   P |- I[n/0,m/0,c/0,r/N+1]  (trivial)

Many-fold step restore:
-----------------------

   case V[m]==0 :
        n =n + \chi(n==m);
        m=m+1 ;
   case V[m]==1 and c<K :
        c = c + \chi(V[n]==1);
        if (c==K) r = min(r,n+1-m);
        n = n + 1;
   case V[m]==1 and c==K :
        c= c- 1;
        m= m+1;
   esac

   I and B |- V[m]==0 -> I[m/m+1,n/n+(n==m)]
   I and B |- V[m]==1 and c<K -> I[n/n+1,c/c+(V[n]==1),r/c+(V[n]==1)?r:min(r,n+1-m)] (hard)
   I and B |- V[m]==1 and c==K -> I[m/m+1,c/c-1]

   (In any branch quota 2N-m-n decreases)


Pseudocode:
------------

 n,m,c,r = 0,0,0,N+1  
 while n<N && (N-n) >= (K-c)
   case V[m]==0 :
        n =n + \chi(n==m);
        m=m+1 ;
   case V[m]==1 and c<K :
        c = c + \chi(V[n]==1);
        if (c==K) r = min(r,n+1-m);
        n = n + 1;
   case V[m]==1 and c==K :
        c= c- 1;
        m= m+1;
   esac
 done

*/

#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

#define MAX 10000

/* NOTE: See the pseudocode:
   _continue_ tabou  is used to simulate multiple case programming
   (easy to read with explicit guards, not the ifthenelse)
   IT IS indeed structured programmingm, Donald Knuth claims )*/
int solve(const int V[], const int N, const int K)
{
  int n,m,c,r;
  for(n=m=c=0,r=N+1; n<N && (N-n) >= (K-c) ; )
    {
      if (V[m]==0)
            {
	      n += (n==m) ;
	      m++ ;
	      continue ;
	    }
      if ((V[m]==1) and (c<K))
	    {
	      c+=(V[n]==1);
	      if (c==K) r = min(r,n+1-m);
	      n++;
	      continue;
	    }
      if ((V[m]==1) and (c==K))
            {
	      c--;
	      m++;
	      continue;
	    }
    }
  return r;
}


int main(int argc, char *args[])
{
  int N,K;
  int V[MAX];
  for(cin >> N; N>=0 ; cin >> N)
    {
      for(int n=0; n< N; n++) cin >> V[n];
      cin >> K ;
      cout << solve(V,N,K) << endl;
    }
}
