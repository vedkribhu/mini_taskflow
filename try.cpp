#include <bits/stdc++.h>
using namespace std;
#include "executor.hpp"
#include <unistd.h>
#define Sleep(X) usleep(X * 1000)
#include <chrono> 
using namespace std::chrono; 
  




void fun1(){
	cout<<"Function 1 start!\n";
	Sleep(500);
	cout<<"Function 1 finish!\n";
}
void fun2(){
	cout<<"Function 2 start!\n";
	Sleep(500);
	cout<<"Function 2 finish!\n";
}
void fun3(){
	cout<<"Function 3 start!\n";
	Sleep(1000);
	cout<<"Function 3 finish!\n";
}
void fun4(){
	cout<<"Function 4 start!\n";
	Sleep(1000);
	cout<<"Function 4 finish!\n";
}
void fun5(){
	cout<<"Function 5 start!\n";
	Sleep(1000);
	cout<<"Function 5 finish!\n";
}
void fun6(){
	cout<<"Function 6 start!\n";
	Sleep(1000);
	cout<<"Function 6 finish!\n";
}
void fun7(){
	cout<<"Function 7 start!\n";
	Sleep(3000);
	cout<<"Function 7 finish!\n";
}
void subflow_fun(){
	cout<<"subflow fun start\n";
	cout<<"subflow fun end\n";
}

int main(){
	auto start = high_resolution_clock::now();
	Taskflow myflow = Taskflow("myflow");
	auto A = myflow.add({
		fun1,
		fun2, 
		fun3, 
		fun4,
		fun5, 
		fun6,
		fun7
	});

	A[1]->precede({A[0]});
	A[2]->precede({A[0]});
	A[3]->precede({A[0]});
	A[4]->precede({A[3], A[1]});
	A[5]->precede({A[3],A[1]});
	A[6]->precede({A[4],A[2]});
	Subflow sub1("sub1");
	sub1.add({
		fun1,
		subflow_fun
	});
	A[6]->attach(&sub1);
	// A[6]->dettach();

	Taskflow myflow2 = Taskflow("myflow2");
	auto B = myflow2.add({
		fun1,
		fun2, 
		fun3, 
		fun4,
		fun5, 
		fun6,
		fun7
	});

	B[1]->precede({B[0]});
	B[0]->precede({B[1]});
	B[3]->precede({B[0]});

	// Linear Execution in comments

	// for(auto test: myflow.taskflow[0]->successor){
	// 	test->execute_task();
	// }
	// A[1].execute_task();
	
	Executor exe;

	exe.run({myflow, myflow2});
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<microseconds>(stop - start); 
	cout <<"Total time taken for mini-taskflow:"<< duration.count()/1e6 << endl; 
	return 0;
	// vector<Task> your = myflow.taskflow[0]->successor;


	//Serial execution
	// for(auto task: exe.topological_sort_list){
	// 	task->execute_task();
	// }



}

