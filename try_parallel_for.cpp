#include <bits/stdc++.h>
using namespace std;
#include "executor.hpp"
#include <unistd.h>
#define Sleep(X) usleep(X * 1000)
#include <chrono> 
#include <atomic>
using namespace std::chrono; 
  
float sum = 0.0;
std::mutex mtx;
int num_iter = 10000;
void calc_pi(int i){
  float x = 2*(i%2)-1;
  float d = 2*i-1;
  mtx.lock();
  sum = sum + (x*4)/d;
  mtx.unlock();
}

int main(){
  auto start = high_resolution_clock::now();
  Taskflow myflow = Taskflow("myflow");

  vector<int> v;
  for (int i = 1; i < num_iter; i++)
  {
    v.push_back(i);
  }
  myflow.for_each(v.begin(), v.end(), 1, calc_pi);
  
  Executor exe;

  exe.run({myflow});
  cout<<sum<<endl;
  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<microseconds>(stop - start); 
  cout <<"Total time taken for mini-taskflow:"<< duration.count()/1e6 << endl; 
  return 0;

}

