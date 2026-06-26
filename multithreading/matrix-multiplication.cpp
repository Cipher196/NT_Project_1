#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int n=1000; // size of matrix
int k=100; // range of element of matrix 0 to k 


int main(){
  auto start = chrono::high_resolution_clock::now();

  vector<vector<int>> v(n, vector<int> (n));

  for(auto &x: v){
    for(auto &y: x){
      y=rand()%k; // so number remain in range 0 to k
    }
  }

  vector<vector<int>> a(n, vector<int> (n)); // a = v X v

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      int sum=0;
      for(int k=0; k<n; k++){
        sum+=v[i][k]*v[k][j];
      }
      a[i][j]=sum;
    }
  }


  auto end = chrono::high_resolution_clock::now();

  auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  float time_taken = ms;
  time_taken/=1000;

  cout<<"Time taken by naive matrix multiplication: "<<time_taken<<" Sec \n";
  return 0;
}
