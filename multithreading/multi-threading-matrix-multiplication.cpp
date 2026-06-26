#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>

using namespace std;

int n=1000; // size of matrix
int k=100; // range of element of matrix 0 to k 

void solve(vector<vector<int>> &a, vector<vector<int>> &v, int sr, int er, int sc, int ec){
  for(int i=sr; i<er; i++){
    for(int j=sc; j<ec; j++){
      int sum=0;
      for(int k=0; k<n; k++){
        sum+=v[i][k]*v[k][j];
      }
      a[i][j]=sum;
    }
  }
}

int main(){
  auto start = chrono::high_resolution_clock::now();

  vector<vector<int>> v(n, vector<int> (n));

  for(auto &x: v){
    for(auto &y: x){
      y=rand()%k; // so number remain in range 0 to k
    }
  }

  vector<vector<int>> a(n, vector<int> (n)); // a = v X v

  int mid=n/2;

  thread t1(solve, ref(a), ref(v), 0, mid, 0, mid);
  thread t2(solve, ref(a), ref(v), 0, mid, mid, n);
  thread t3(solve, ref(a), ref(v), mid, n, 0, mid);
  thread t4(solve, ref(a), ref(v), mid, n, mid, n);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

  auto end = chrono::high_resolution_clock::now();

  auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  float time_taken = ms;
  time_taken/=1000;

  cout<<"Time taken by multi-threaded naive matrix multiplication: "<<time_taken<<" Sec \n";
  return 0;
}
