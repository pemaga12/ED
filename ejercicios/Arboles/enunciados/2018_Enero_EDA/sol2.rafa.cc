#include <iostream>
#include <algorithm> // swap, abs

using namespace std;

// Tail recursion

// P : N > 0 , sorted(V)
// V[p]=num
// where p= min p : i <= p < j and |V[p]-x| = minDist(V,i,j,x) :p
// and
// minDist(V,i,j,x) : min p : i <= p < j : |V[p]-x|
int iclosest(const int V[], const int i, const int j, const int x)
{
  if (j==i+1) return V[i]; // size 1
  if (j==i+2) {  // size 2
    if (abs(V[i]-x) <= abs(V[i+1]-x)) return V[i];
    else  return V[i+1];
  }
  if (j > i + 2 )  // 3 or more.
    {
      const int h = (i+j)/2 ;
      if (x<=V[h]) return iclosest(V,i,h+1,x);
      else return iclosest(V,h,j,x);
    }
  return 0; // Never reached.
}

// N > 1 
int closest(const int V[], const int N, const int x)
{
  return iclosest(V,0,N,x);
}


#define MAX 100000

int main(int argc, char *args[])
{
  int C ;
  int x, N;
  int V[MAX] ;
  cin >> C ;
  for (int c=0; c<C; c++)
    {
      cin >> x >> N ;
      for (int n=0 ; n<N ; n++) cin >> V[n];
      cout << closest(V,N,x) << endl;
    }
  return 0;
}
