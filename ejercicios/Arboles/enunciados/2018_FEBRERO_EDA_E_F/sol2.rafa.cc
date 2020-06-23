/*
  Note: N=1 makes  case a bit more complicated.

  Formal Spec (Hard, not required):
  ---------------------------------

  P : N > 0 and sorted(V,0,N)
      N-1 = #i : 0 <= i < N : V[i]%2 = 0 and
      (N=1 || V[N-1] - V[0] < 2*(N-1))

    int odd(V[0..N) of int ) 

  Q : 0 <= p < N and V[p]%2=1


   0     p                       N
   +-----+-----+-----+-----+-----+
   |  4  |  5  |  6  |  8  | 10  |
   +-----+-----+-----+-----+-----+
   
   0                 p           N
   +-----+-----+-----+-----+-----+
   |  4  |  6  |  8  |  9  | 10  |
   +-----+-----+-----+-----+-----+


   0                       p     N
   +-----+-----+-----+-----+-----+
   |  4  |  6  |  8  |  10 | 11  |
   +-----+-----+-----+-----+-----+


Inversion (tail recursion)
--------------------------

I : P[0/i,N/j] and 0 <= i < j <= N
int oddG(V[i..j)) 
Q  

Snapshot for I
--------------

  i=0          p                 j=N
   +-----+-----+-----+-----+-----+
   |  4  |  6  |  8  |  9  | 10  |
   +-----+-----+-----+-----+-----+

Init:
-----

  i,j = 0, N


Trivial: (Basis)
---------------
B
   (j-i)=1  -> V[i]
   (j-i)=2 && V[i]%2=0 => V[i+1]
   (j-i)=2 && V[i]%2=1 => V[i]
   (j-i)>2 && (V[half]%2=1) -> V[half]
  

where half = (j+i)/2 .

Quote(j,i) = (j-i) >= 1 >=  0 
----------

Sucessor(V,i,j) :- 
-----------------
(j-i)>2

   case **
     V[j-1]-V[half]<2*(j-half-1) -> i,j = half,j
     V[half]-V[i]<2*(half-i) -> i,j = i, half+1
   esac


O(log(j-i)), since n=(j-i) , then
    T(n)= T(n/2) + c

*/

#include <iostream>

using namespace std;

#define MAX 100000


int oddG(const int V[], const int i, const int j)
{
  const int half = (i+j)/2 ;
  if ((j-i)==1) return i;
  if ((j-i)==2 && (V[i]%2)) return i;
  if ((j-i)==2 && !(V[i]%2)) return (i+1);
  if (((j-i)>2) && (V[half]%2)) return half;

  // Recursive cases
  if ((V[j-1]-V[half]) < (j-half-1)*2) return oddG(V,half,j);
  else return oddG(V,i,half+1);
}

int odd(const int V[], const int N)
{
  return oddG(V,0,N);
}


int main(int argc, char **args)
{
  int N;
  int V[MAX];
  cin >> N;
  for ( ; N ; cin >> N)
    {
      for (int n=0; n<N ; n++) cin >> V[n];
      cout << V[odd(V,N)] << endl;
    }
  return 1;
}
