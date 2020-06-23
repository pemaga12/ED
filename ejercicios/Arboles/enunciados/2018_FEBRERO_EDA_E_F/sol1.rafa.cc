/*

0)  Spec

    P : V[0..N) , N>0
    Q : M = max i,j : 0<= i < j <= N and AllConsec(V,i,j) : j - i
        b = min i : 0 <= i <= N and AllConsec(V,i-M,i) : i-M



1) Note: Consider semi open intervals [i..j), no [i..j] as in exercise

 [3,4)  [3,3)   [3,5)

 AllConsec(V,i,j) := \forall k: i<=k<j-1 : V[k]+1=V[k+1]

2) Note: Using V[0..N) instead of 'sequence' as in exercise

 MaxSequence(V[0..N),L) := L = max i,j : 0 <= i < j <=N and AllConsec(V,i,j): j-i


3) I :  Q[N/n] and 1 <= n <= N and
        m = max i : 0<=i<n and AllConsec(V,i,n):n-i  *

        ** efficiency reasons

   !B : n=N 

    B : n < N         


Invariant snapshot:
-------------------
0  --M=3, b=0----                             --m=1-- n     N
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-...-+
|  0  |   1 |  2  |  2  |  3  |  4  |  3  |  4  |  1  |     |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-...-+


I and n=N => Q 

Cuota(N,n)= N-n

Init:
-----
   n,M,m,b = 1,1,1,0 


Step:
-----
   n = n + 1

Restore:
--------
   
   let 
      m = max i : 0<=i<n+1 and AllConsec(V,i,n+1):n+1-i  
   in
     case max(m,M) > M :
         M,b = m,n+1-m

 *   m addded effectively to invariant for efficiency reasons
     Hence, we have to restore it, always...


   case V[n-1]+1 = V[n] :
           m = m + 1;
           case max(m,M)>M
              M,b = m,n+1-m
   e.o.c
           m = 1 
        
Pseudocode:
------------

   n,M,m,b = 1,1,1,0 
   while (n<N)
      case V[n-1]+1 = V[n] :
           m = m + 1;
           case max(m,M)>M
              M,b = m,n+1-m
      e.o.c
           m = 1 
   end

Complexity in O(N), since body is in O(1) and iter in O(N)

*/

#include <iostream>

using namespace std;

#define MAX 100000

void foo(const int V[], const int N, int &M, int &b)
{
  int n,m;
  for (b=0, n=M=m=1; n<N ; n++)
    {
      if ((V[n-1]+1)==V[n])
	{
	if (max(++m,M)>M)
	  {
	    M=m;
	    b = n+1-m;
	  }
	}
      else m=1 ;
    }

}

int main(int argc, char **args)
{
  int N;
  int V[MAX];
  int b,M;
  cin >> N;
  for ( ; N ; cin >> N)
    {
      for (int n=0; n<N ; n++) cin >> V[n];
      foo(V,N,M,b);
      cout << b << " " << M << endl;
    }
  return 1;
}
   




