
#include <bits/stdc++.h>
using namespace std;

class Subflow;
class Task {
	// friend class graph;
	// friend class executor;

	public:
		int id;
		vector<Task*> successor;
		vector<Task*> predecessor;
		atomic<int> dependency;
		Subflow* subflow;


		function<void()> fun;
		

	    bool operator <(const Task& rhs) const
	    {
	        return id < rhs.id;
	    }

		void execute_task(){
			(this->fun)();
		}
		void attach(Subflow* sub){
			this->subflow = sub;
		}
		void detach(){
			this->subflow = NULL;
		}

		void succeed(vector<Task*> input){
			for(auto task: input){
				this->successor.push_back(task);
				task->predecessor.push_back(this);
				this->predecessor.push_back(task);
				task->successor.push_back(this);
			}
		}
		void precede(vector<Task*> input){
			for(auto task: input){
				this->dependency++;
				this->predecessor.push_back(task);
				task->successor.push_back(this);
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

