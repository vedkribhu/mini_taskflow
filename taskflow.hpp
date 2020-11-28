#include <bits/stdc++.h>
#include "subflow.hpp"
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

		int total_task = 0;
		// input -> vector of function pointers, output-> vector of pointers Tasks
		vector<Task*> add(vector<void (*)()>input){
			// vector<Task*> output;
			for(int i=0;i<input.size();i++){
				Task* A = new Task();
				A->fun = bind(input[i]);
				A->id = (this->total_task)++;
				taskflow.push_back(A);
			}
			return taskflow;
		}

		vector<Task*> topological_sort_list;
		
		
		// to mark visited while dfs
		vector<int> color;
		// task to id map



		//returns false if there is a cycle, 
		// also populates the topological sort list. 
		bool dfs(int node_id){
			// cout<<"\n"<<node_id<<" my successors: ";
			if((this->color)[node_id]==0){
				(this->color)[node_id]=1;
				for(auto task: this->taskflow[node_id]->successor){
					int id = task->id;
					bool flag = this->dfs(id);
					if(!flag) return false;
				}	
				// cout<<"\n";
				if(this->taskflow[node_id]->subflow!=NULL){
					this->taskflow[node_id]->subflow->build();
					for(Task* subflow_task: this->taskflow[node_id]->subflow->topological_sort_list){
						this->topological_sort_list.push_back(subflow_task);
					}
				}
				this->topological_sort_list.push_back(this->taskflow[node_id]);
				(this->color)[node_id] = 2;
				return true;

			}
			// cycle detected
			else if(color[node_id]==1){
				return false;
			}
			return true;
			

		}

		
		void build(){
			// building taskflow tasks -> id map
			int i=0;
			for(auto task: this->taskflow){
				// task->id = i;
				this->color.push_back(0);
				i++;
			}

			bool flag=true;
			for(int i=0;i<this->total_task;i++){ 
				if(color[i]==0){
					flag = flag & this->dfs(i);
				}
			}
			if(!flag){
				this->topological_sort_list.clear();
				cout<<"given graph in Taskflow:"<<this->name<<" has cycle, deadlock can not be resolved. Routine Skipped\n";
				// exit(1);
			}
			// reverse(topological_sort_list.begin(), topological_sort_list.end());
			return;
		}


		void dump(ofstream &myfile){
			myfile << "digraph gr { \n";

			for(int node_id=0; node_id<this->total_task;node_id++){
				bool flag=false;
				for(auto task: this->taskflow[node_id]->successor){
					flag=true;
					// "subflow:"+this->name+":"+node_id
					myfile<<"taskflow_"<<this->name<<"_"<<node_id<<"->"<<"taskflow_"<<this->name<<"_"<<task->id<<";\n";
				}
				if(this->taskflow[node_id]->subflow!=NULL){
					this->taskflow[node_id]->subflow->dump(myfile,"taskflow_"+this->name+"_"+to_string(node_id));
				}
				if(!flag){
					myfile<<"taskflow_"<<this->name<<"_"<<node_id<<";\n";
				}

			}
			myfile << "}"; 
			
		}


		template <typename B, typename E, typename S, typename C>

		void for_each(B&& beg, E&& end, S&& inc, C&& cal){
			int n = distance(beg, end);
			n = n/inc;
			while(n-- > 0){
				Task *A = new Task();
				A->fun = bind(cal, *beg);
				A->id=(this->total_task)++;
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
