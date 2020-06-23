/*

  Intersection possitions on strict polygonal lines.

  (Spec. Not required)


   P : N-0>=2 strictInc(V[0..N)) and   strictDec(W[0..N))
   cross(V[0..N),W[0..N)) return n
   Q : n = max p : 0 <= p + 1 <= N and (p >= 0 -> V[p]<=W[p]):p

   ** N-0 is on purpose for syntatic replacement.

Visual Snapshot:  (hard to depict in ASCII)
----------------

    Our point lies between on V[i..j) or (-i-1,i) or (j-1,j)

  Tail approach Immersion:
  ----------------------------
  P' : Q[N-0/j-i,0/i,N/j] and 0<=i < j <= N
  crossG(V[i..j),W[i..j)) return n
  Q' : Q 

  Init call
  ----------
  
     crossG(V[0..N],W[0..N))

  Pseudocode:
  -----------

    let h = (i+j)/2
 
       V[h]=W[h]  -> h  (Basis)

       V[h]<W[h]  ->
                 (j - h) >= 2 -> crossG(V,W,h,j)  (Recursuive)
                 e.o.c     -> h  (Basis)
       V[h]>W[h]  ->
                 (h-i) >= 2 -> crossG(V,W,i,h)  (Recursuive)
                 e.o.c     ->
                             V[i]>W[i] -> i - i  (Basis)
                             V[i]<=W[i] -> i   (Basis)

Proof: (Not required)
---------------------

  Note: numberes lines must computer-aided proof.

   - Sound immersion:

      1 .- P' and i=0 and j=N  and Q' |- Q  

   - Full cases range

      2 .- P' |- (V[h]=W[h] ||
                  V[h]<W[h] and (j-h>=2 || j-h < 2) ||
                  V[h]>W[h] (h-i>=2 || h-i < 2))

   - Success for Trivial
      3 .- P' and V[h]=W[h] |- Q'
      4 .- P' and V[h]<W[h] and j-h<2 |- Q'
      5 .- P' and V[h]>W[h] and h-i<2 and V[i]>W[i] |- Q'
      6 .- P' and V[h]>W[h] and h-i<2 and V[i]<=W[i] |- Q'

   - Success for recursive:
      7 .- P' and V[h]<W[h] and (j-h>=2) and Q' |- Q'
      8 .- P' and V[h]>W[h] and (h-i>=2) and Q' |- Q'

   - Positive defined Quota:
      9.- P' |- (j-i) >= 0

   - Decreasing quota:
      10 .- P' and V[h]<W[h] and (j-h>=2) |- (j-h) < (j-i)
      11 .- P' and V[h]>W[h] and (h-i>=2) |- (h-i) < (j-i)

   -  Init call:
      9 .- |- P'[i/0,j/N]

Acording to Theorem of Division, A=1, B=2, and k=0, hence O(log(n))
*/

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX 1000

/* Inmmersion */
int crossG(const int V[],const int W[], const int N,
	   const int i, const int j)
{
  //  cout << i << " " << j << endl;
  const int h = (i+j)/2 ;
  if (V[h]==W[h])  return h;
  if (V[h]<W[h])
    {
      if ((j-h)>=2) return crossG(V,W,N,h,j);
      return h;
    }
  if (V[h]>W[h])
    {
      if ((h-i)>=2) return crossG(V,W,N,i,h);
      if (V[i]>W[i]) return i-1;
      return i;
    }
  return -5 ; // (Never reached)
}

void cross(const int V[], const int W[], const int N, int &n, int &m)
{
  n = crossG(V,W,N,0,N);
  m = n + 1 ;
  return ;
}



int main(int argc, char *args[])
{
  int N ;
  int V[MAX],W[MAX];
  int n,m;
  for (cin >> N  ; N; cin >> N)
    {
      for (int n=0; n<N; n++) cin >> V[n];
      for (int n=0; n<N; n++) cin >> W[n];
      cross(V,W,N,n,m);
      cout << n << " " << m << endl;
    }
  return 0;
}


/*

5
1 3 4 7 8
8 7 4 2 1
2 3
6
-5 -3 -1 0 4 7
9 6 5 2 1 0

3 4
6
1 3 4 5 7 8
-1 -2 -4 -5 -7 -8
-1 0
6
1 3 4 5 7 8 
17 14 12 11 9 8 
5 6
0



*/
