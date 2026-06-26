#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> counter(0);

void add(){
  for(int i=0; i<2000000; i++){
    counter++;
  }
}

int main(){
  thread t1(add);
  thread t2(add);

  t1.join();
  t2.join();

  cout<<counter<<endl;
  return 0;
}
