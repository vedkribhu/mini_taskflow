#include <bits/stdc++.h>
#include "task.hpp"
#include "PARAMS.hpp"

// #include "executor.hpp"
using namespace std;


class Subflow {
	// friend class graph;
	// friend class executor;

	public:

		vector<Task*> subflow;
		string name;
		Subflow(string name="default"){
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
				subflow.push_back(A);
			}
			return subflow;
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
				for(auto task: this->subflow[node_id]->successor){
					int id = task->id;
					bool flag = this->dfs(id);
					if(!flag) return false;
				}	
				// cout<<"\n";
				if(this->subflow[node_id]->subflow!=NULL){
					this->subflow[node_id]->subflow->build();
					for(Task* subflow_task: this->subflow[node_id]->subflow->topological_sort_list){
						this->topological_sort_list.push_back(subflow_task);
					}
				}
				this->topological_sort_list.push_back(this->subflow[node_id]);
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
			// building subflow tasks -> id map
			int i=0;
			for(auto task: this->subflow){
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
				cout<<"given graph in Subflow:"<<this->name<<" has cycle, deadlock can not be resolved. Routine skipped\n";
				// exit(1);
			}
			// reverse(topological_sort_list.begin(), topological_sort_list.end());
			return;
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
				subflow.push_back(A);
			}

		 }
};


// int main(){
// 	Subflow reddy = Subflow("reddy");
// 	auto A = reddy.add({
// 		[](){cout<<"Mc";},
// 		[](){cout<<"Bc";}
// 	});


// 	A[1]->execute_task();
// }
