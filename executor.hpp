#include <bits/stdc++.h>
#include "taskflow.hpp"

using namespace std;


class Executor {
	// friend class task;
	// friend class taskflow;
	public:
		Executor(){};
		Taskflow current_taskflow;
		vector<Task*> topological_sort_list;
		int total_task = 0;
		// to mark visited while dfs
		vector<int> color;
		// task to id map



		//returns false if there is a cycle, 
		// also populates the topological sort list. 
		bool dfs(int node_id){
			// cout<<"\n"<<node_id<<" my successors: ";
			if(color[node_id]==0){
				color[node_id]=1;
				for(auto task: this->current_taskflow.taskflow[node_id]->successor){
					int id = task->id;
					cout<<node_id<<"->"<<id<<"\n";
					bool flag = dfs(id);
					if(!flag) return false;
				}	
				// cout<<"\n";
				topological_sort_list.push_back(this->current_taskflow.taskflow[node_id]);
				color[node_id] = 2;
				return true;

			}
			// cycle detected
			else if(color[node_id]==1){
				return false;
			}
			return true;
			

		}

		
		void build(Taskflow taskflow){
			// building taskflow tasks -> id map
			int i=0;
			for(auto task: taskflow.taskflow){
				// task->id = i;
				color.push_back(0);
				i++;
			}
			this->total_task = i;
			bool flag=true;
			for(int i=0;i<total_task;i++){ 
				if(color[i]==0){
					cout<<"calling dfs for "<<i<<"\n";
					flag = flag & dfs(i);
				}
			}
			if(!flag){
				topological_sort_list.clear();
				perror("given graph has cycle, deadlock can not be resolved\n");
				exit(1);
			}
			reverse(topological_sort_list.begin(), topological_sort_list.end());
			return;
		}


		void run(Taskflow taskflow){
			this->current_taskflow = taskflow;
			// graph build 
			this->build(taskflow);
			
			// algorith start -- threads
		}

};
