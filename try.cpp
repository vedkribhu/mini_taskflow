#include <bits/stdc++.h>
using namespace std;
#include "executor.hpp"

void sayThanks(){
	cout<<"Thnx\n";
}

int main(){
	Taskflow myflow = Taskflow("myflow");
	auto A = myflow.add({
		[](){cout<<"Thank you!\n";},
		[](){cout<<"Arigato Gozaimas!\n";},
		[](){cout<<"Merci Boccu!\n";},
		[](){cout<<"Xièxiè!\n";},
		sayThanks
	});

	A[0]->precede({A[1], A[2]});
	A[3]->precede({A[2], A[0]});
	A[1]->precede({A[4]});
	

	// for(auto test: myflow.taskflow[0]->successor){
	// 	test->execute_task();
	// }
	// A[1].execute_task();
	
	Executor exe;
	exe.run(myflow);
	// vector<Task> your = myflow.taskflow[0]->successor;
	cout<<"Top list:";
	for(auto task: exe.topological_sort_list){
		cout<<task->id<<" ";
	}
	cout<<"\n";

	//Serial execution
	for(auto task: exe.topological_sort_list){
		task->execute_task();
	}



}

