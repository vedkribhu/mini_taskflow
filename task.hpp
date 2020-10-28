#include <bits/stdc++.h>
using namespace std;


class Task {
	// friend class graph;
	// friend class executor;

	public:
		int id;
		vector<Task*> successor;
		vector<Task*> predecessor;
		int dependency=0;

		function<void()> fun;

	    bool operator <(const Task& rhs) const
	    {
	        return id < rhs.id;
	    }

		void execute_task(){
			(this->fun)();
		}

		void succeed(vector<Task*> input){
			for(auto task: input){
				this->predecessor.push_back(task);
				task->successor.push_back(this);
			}
		}
		void precede(vector<Task*> input){
			for(auto task: input){
				this->dependency++;
				this->successor.push_back(task);
				task->predecessor.push_back(this);
			}
		}
};

// void fun(){
// 	cout<<"Hello";
// }

// int main(){
	
// 	Task A = Task();	
// 	Taskflow An = Taskflow();
// 	An.add(A);
// 	A.fun = bind(&fun);
// 	A.execute_task();
// }

