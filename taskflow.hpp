#include <bits/stdc++.h>
#include "task.hpp"
#include "PARAMS.hpp"

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
		template <typename B, typename E, typename S, typename C>

		void for_each(B&& beg, E&& end, S&& inc, C&& cal){
			int n = distance(beg, end);
			n = n/inc;
			while(n-- > 0){
				Task *A = new Task();
				A->fun = bind(cal, *beg);
				advance(beg, inc);
				taskflow.push_back(A);
			}


		 	// int w = NUMBER_OF_THREADS;
		 	// int n = distance(beg, end);



		 	// cout<<n<<" "<<w;
		 	// cal(1);
		 	// n = n/inc;

		 	// if(n<w){w = n;}

		 	// for(int i=w; i>=0; i--){
			 // 	Task* A = new Task();

			 // 	A->fun = bind([](){
			 // 		B it = beg;
			 // 		cal(it); 
			 // 		while(advance(it, ))
			 // 	});

			 // 	advance(beg, inc);
			 // 	taskflow.push_back(A);
			 // 	if(beg>=end){break;}
		 	// }
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
