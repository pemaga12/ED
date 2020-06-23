/*
  Number of Maximal Segments.

 Sol By Rafael Martinez

  P : N >= 0 and l > 1 
  Q : num = #p,q : 0 <= p <= q <= N : q-p >= l and AllesMaximumFlat(V,p,q,N,l) 

where

  AllesMaximumFlat(V,i,j,n)::= ** Hard!
      j = min p : i <= p <= n and (p<n -> |V[p]-V[p-1]|> 1) : p and
      i = max p : 0 <= p <= j and (p>0 -> |V[p-1]-V[p]|> 1) : p  


(Visual idea of AllesMaximumFlat)

AllesMaximumFlat(V,1,6,6,2)  but not AllesMaximumFlat(V,1,4,6,2)!

0    i=1    2     3     4     5    j=n=6  7     8     9    10     11    N
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-...-+
|  1  |  3  |   4 |  3  |  4  |  3  |  4  | 8   | 10  | 14  |  16 |     |
+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-...-+

  I:Q[N/n] and min(N,1) <= n <= N and  AllesMaximumFlat(V,left,n,n)

  C(n) = N-n >= 0 

  I and n=N |- Q   (trivial)


   Init:
   -----
   
   n,num,left= min(N,1),0,0

  P |- I[n/min(N,1),num/0,left/0]   (trivial)

   Step:
   -----
   n = n + 1  (Cuota decreases)

   Restore: 
   --------

   case |A[n]-A[n-1]|<=1 and 
       num = num +  \chi(n-left == l - 1)
   case |A[n]-A[n-1]|>1
       left = n 

   Not trivial: (Not required)

   I and B |- (|A[n]-A[n-1]|<=1 ) -> I[n/n+1][num/num+\chi(n-left = l - 1) ]
   I and B |-  |A[n]-A[n-1]|> 1 -> I[n/n+1][left/n]


   Every expression and assigment in body are O(1).Since the
   loop executes in O(N), we have a total complexity of O(N)

*/ 

#include <iostream>
#include <algorithm> // max

#define MAX 10000

using namespace std;

/* C version */
int ex1(const int V[], const int N,const int l)
{
  int left,n,num;
  for(n=min(N,1),num=left=0;n<N; n++)
    if (abs(V[n]-V[n-1])<=1)
      num += (n-left)==(l-1);
    else
      left = n ;
  return num;
}


int main(int argc, char *args[])
{
  int N,L;
  int V[MAX];
  for(cin>>N>>L; N || L ; cin>>N>>L)
    {
      for(int n=0; n<N; n++) cin>>V[n];
      cout << ex1(V,N,L) << endl;
    }
  return 0;
}

/*
10 3
5 5 3 4 3 4 7 8 9 3
2
5 2
5 4 4 5 6
1
6 3
4 6 8 2 5 9
0
6 6
3 4 3 2 5 4
0
0 0
*/
