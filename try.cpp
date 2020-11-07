#include <bits/stdc++.h>
using namespace std;
#include "executor.hpp"

void sayThanks(){
	cout<<"E\n";
}

int main(){
	Taskflow myflow = Taskflow("myflow");
	auto A = myflow.add({
		[](){cout<<"A!\n";},
		[](){cout<<"B!\n";},
		[](){cout<<"C!\n";},
		[](){cout<<"D!\n";},
		sayThanks
	});

	A[3]->precede({A[1], A[2]});
	A[1]->precede({A[0]});
	A[2]->precede({A[0]});
	// A[3]->precede({A[2], A[0]});

	// for(auto test: myflow.taskflow[0]->successor){
	// 	test->execute_task();
	// }
	// A[1].execute_task();
	
	Executor exe;

	exe.run(myflow);
	// vector<Task> your = myflow.taskflow[0]->successor;


	//Serial execution
	for(auto task: exe.topological_sort_list){
		task->execute_task();
	}



}

