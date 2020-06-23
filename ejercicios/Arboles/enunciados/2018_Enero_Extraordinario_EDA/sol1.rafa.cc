
/*
  As a decission problem, we transform it into a optimization problem

  P : N >= 0 and sorted(V)
  Q : N = min i : 0 <= i <= N and (i < N -> R(V,i)) : i
      and MM <= M

  where

  R(V,i) ::= ( i > 0 && (V[i]!=V[i-1])
                       (j = min k : 0 <= k < i and AllesEq(V,k,i) : k)
                       (q = min k : 0 <= k <= j and AllesEq(V,k,i) : k)
                       (i-j) < (j - q) )

  M = max p : 0 <= p <= N and AllEq(V,p,N) : N - p 
  MM = max p : 0 <= p <= N-M and AllEq(V,p,N-M) : N-M - p 
		       
don't scare!  

Informally, we are searching for the first pos (min i)
such that beeing different to the previous (V[i]!=V[i-1]), ends an
step whose length (i-j) is less than the previous (j-q). If such a pos
does not exists, (i=N), the actual step musts be at least as longer as
the previous (MM<=M)



0        n-M-MM              n-M          n                 N
+-----+-----+-----+-----+-----+-----+-----+-----+-...-+-----+
|  1  |  1  |  3  |   3 |  3  |  4  |  4  |  4  |     |     |
+-----+-----+-----+-----+-----+-----+-----+-----+-...-+-----+
                 MM=3               M=2


  I  : Q[N/n] and 0 <= n <= N and

  B  : (n<N) && (MM <= M || (n==0) || V[n]==V[n-1])   **

  ** I and n==0 => MM <= M , and (n==0) can be ommited in B

  
  C(N,n) = N-n >= 0 


  Step:
  -----
     n = n + 1 (Clearly , quota decreases)
     

  Init:
  -----
     n,M,MM = 0, 0, 0

  Restore:
  -------
     case n>0 && V[n]==V[n-1]
         M = M + 1    
     eoc
         M, MM = 1 , M
     esac


So we have




  Pseudocode:
  -----------
     n,M,MM = 0, 0, 0
     while (n<N) && (MM <= M || V[n]==V[n-1])
       case n>0 && V[n]==V[n-1]
         M = M + 1    
       eoc
         M, MM = 1 , M
       esac
       n = n + 1
     done
     return n==N && MM <= M ;


    
*/

#include <iostream>   // cin, cout
#include <algorithm>  // swap

using namespace std;

#define MAX 1000

/* See full development and derivation below */
bool stairs (const int V[], const int N)
{
  int n,M,MM;
  for (n=M=MM=0; (n < N) && (MM<=M || (V[n]==V[n-1])) ; n++)
    if (n &&  (V[n]==V[n-1]))
      M += 1 ;
    else
      { 
	MM = M;
	M = 1 ;
      }
  return ((n==N) && (MM <= M));
}

int main(int argc, char *args[])
{
  int N;
  int V[MAX];
  for (cin >> N  ; N ; cin >> N)
    {
      for(int n=0;n<N;n++)  cin >> V[n];
      cout << (stairs(V,N)?"SI":"NO") << endl;
    }

  return 0 ;
}
