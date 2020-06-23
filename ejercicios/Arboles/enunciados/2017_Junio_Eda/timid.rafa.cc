// C/C++ flavour style.
#include <iostream>  // cin, cout

using namespace std;

int line(const int V[], const int N)
{
  for(int n=0 ; n < N ; n++) cout << V[n] << " " ;
  cout << endl;
}

// naive valid(k):  (O(N) in auxiliary space.)
// 
// count[k] < k && (n==0 or V[n-1] <= k)
// Then, mark and unmark acordingly.

// IO()
void timid(int V[], const int N,
	  const int n,
	  const int ini, const int fin )
{
  for (int k=n?V[n-1]:ini ; k <= fin ; k++)
    {
      // valid(k)?
      if ((n-k) < 0 || (k && (V[n-k] < k))) // k is a hack to avoid case ini=0
	{
	  V[n]= k;
	  if (n==N-1)
	    line(V,N);
	  else
	    timid(V,N,n+1,ini,fin);
	}
    }
  return ;
}

#define MAX 10000
int main(int argc, char **args)
{
  int N,ini,fin;
  int V[MAX];
  for( ; cin >> N >> ini >> fin; ) timid(V,N,0,ini,fin);
}
