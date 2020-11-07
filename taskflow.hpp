#include <bits/stdc++.h>
#include "task.hpp"

// #include "executor.hpp"
using namespace std;


class Taskflow {
	// friend class graph;
	// friend class executor;

	public:

		vector<Task*> taskflow;
		string name;
		Taskflow(string name="default"){
			this->name = name; 
		}
		// input -> vector of function pointers, output-> vector of pointers Tasks
		vector<Task*> add(vector<void (*)()>input){
			// vector<Task*> output;
			for(int i=0;i<input.size();i++){
				Task* A = new Task();
				A->fun = bind(input[i]);
				A->id = i;
				taskflow.push_back(A);
			}
			return taskflow;

		}
};


// int main(){
// 	Taskflow reddy = Taskflow("reddy");
// 	auto A = reddy.add({
// 		[](){cout<<"Mc";},
// 		[](){cout<<"Bc";}
// 	});


// 	A[1]->execute_task();
// }
