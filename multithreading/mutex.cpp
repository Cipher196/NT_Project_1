#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter=0;
mutex mx;

void add(){
  lock_guard<mutex> lock(mx);
  for(int i=0; i<1000000; i++){
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
