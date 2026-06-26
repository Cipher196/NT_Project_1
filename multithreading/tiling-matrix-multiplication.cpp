#include <chrono>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

int n=1000; // size of matrix
int k=100; // range of element of matrix 0 to k 
int bs=64; // block size


int main(){
  auto start = chrono::high_resolution_clock::now();

  vector<vector<int>> v(n, vector<int> (n));

  for(auto &x: v){
    for(auto &y: x){
      y=rand()%k; // so number remain in range 0 to k
    }
  }

  vector<vector<int>> a(n, vector<int> (n)); // a = v X v

  for(int ii=0; ii<n; ii+=bs){
    for(int jj=0; jj<n; jj+=bs){
      for(int kk=0; kk<n; kk+=bs){

        for(int i=ii; i<min(ii+bs,n); i++){
          for(int j=jj; j<min(jj+bs,n); j++){
            for(int k=kk; k<min(kk+bs,n); k++){

              a[i][j]+=v[i][k]*v[k][j];

            }
          }
        }

      }
    }
  }

  auto end = chrono::high_resolution_clock::now();

  auto ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

  float time_taken = ms;
  time_taken/=1000;

  cout<<"Time taken by tiling matrix multiplication: "<<time_taken<<" Sec \n";
  return 0;
}
