/*
  Recursive : sumdivisible 

  As a decission problem, we model it as optimization problem. (min,max)

(Spec not required )

  P : N > 0 
  sumDivisible(N) return b
  Q : b = \max i :0+0 <= i <= ceillog(N) and ((i>0)-> (sum(N,i,ceillog(N)) % i) != 0):i  *

	* 0+0 is on purpose to make syntatic expression substitution.


  where ceillog(N) = 1 + min i : 0 <= i : 10^i <= N
        (Informally, ceilog marks the number of cyphres)
        
        sum(N,i,A) = \sum j : A-i <= j < A : (N/10^(log(N)-j))%10
        (Informally Summing up to i digits)

Visual snaphost
---------------
  33374 -> 1 (YES)

     3 + 3 + 3 + 7 + 4 = 20 = sum(33374,5,5) % 5 =0 
     3 + 3 + 3 + 7     = 16 = sum(33374,4,5) % 5 =0 
     3 + 3 + 3         = 9  = sum(33374,3,5) % 5 =0 
     3 + 3             = 6  = sum(33374,2,5) % 5 =0 
     3                 = 3  = sum(33374,1,5) % 5 =0 

  33373 -> 0 (NO)

     3 + 3 + 3 + 7 + 4 = 19 = sum(33374,5,5) % 5 !=0 

  Tail approach Immersion:
  ----------------------------

  P' : 0<= n <= ceillog(N) and
       0 <= NN <= N and NN=N/10^(ceillog(N)-n)
       ac = sum(N,n,ceillog(N)) ** efficiency reaons.
       n<ceillog(N) -> Q[0+0/n+1]
  sumDivisibleG(N,NN,n,ac) return b
  Q' : Q

  ** efficiency reasons.

  Init call
  ---------
  let 
     ac = sum(N,0,log(N))
     n  = ceillog(N)
  in
  sumDivisibleG(N,N,n,ac)

  Pseudocode:
  ----------- 
  General case: 

   n>0 and ac % n==0 -> sumDivisibleG(N,NN/10,n-1,ac-(NN%10))


  Basis case:

   n==0 -> n
   n>0 and ac % n!=0 -> n

Acording to Theorem of Division, A=1, B=2, and k=0, hence O(log(n))

Proof: (Not required)
---------------------
  Note: numberes lines must computer-aided proof.
  Note: warning typos 

   - Sound immersion:

    1 .- P' and n=ceillog(N)) and and N=NN and ac=sum(N,n,n) and Q' |- Q  
  
   - Full cases range

    2 .- P' |- (n==0 || ((n>0) && (ac % n)!= 0 || (ac % n)== 0) )

  - Success for Trivial:
    3 .-  P' and n==0 |- Q'
    4 .-  P' and n > 0 and (ac % n)!=0 |- Q'

  - Precondition holds after recursive call.

    5 .- P' and n > 0 and (ac % n)!=0 |- P'[NN/(NN/10),n/n-1,ac/ac-(NN%10)

  - Success for Recursive:
    6 .- P' and n > 0 and (ac % n)!=0 and Q' |- Q'


  - Positive defined Quota :
    7 .- P' |- NN >= 0 

  - Decreasing quota
    8 .- P' and n > 0 and (ac % n)!=0 |- NN/10 <=  N

  - Init call:
    9 .- |- P'[NN/N,n/ceillog(n),ac=sum(N,ceillog(n),ceillog(n))]
  

*/

#include <iostream>
#include <algorithm>

using namespace std;

/* first parameter can be omitted. Only for predicates*/
int sumDivisibleG(const int N, const int n, const int ac)
{
  if (!n) return n;
  if (n && (ac%n)) return n;
  // (General case : n>0 and ac%n==0)
  return sumDivisibleG(N/10,n-1,ac-(N%10));
}

int sumDivisible(const  int N)
{
  int n,ac;
  int NN = N;
  for( ac=NN%10, n=1 ; NN/10 ; NN/=10) { n++; ac+=(NN/10)%10 ;  } // log(N)
  return (0==sumDivisibleG(N,n,ac)); // log(N)
}

int main(int argc, char *args[])
{
  int N;
  for(cin >> N; N ; cin >> N)
      cout << sumDivisible(N) << endl;
}


//  cout << " N " << N  << " n " << n << " ac " << ac <<endl;
/*
g++ 02Recursion.rafa.cpp -o main && ./main
33374
1
33373
0
84
1
85
0
9
1
0
*/
