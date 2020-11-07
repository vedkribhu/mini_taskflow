#include <bits/stdc++.h>
#include "taskflow.hpp"

using namespace std;

#define NUMBER_OF_THREADS 4;

class Executor {
	// friend class task;
	// friend class taskflow;
	public:
		Executor(){};
		mutex mtx, cv_mtx;
		condition_variable cond_var;
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
					flag = flag & dfs(i);
				}
			}
			if(!flag){
				topological_sort_list.clear();
				perror("given graph has cycle, deadlock can not be resolved\n");
				exit(1);
			}
			// reverse(topological_sort_list.begin(), topological_sort_list.end());
			return;
		}

		static void execute_thread(Executor* exe){
			bool flag=true;
			do {
				exe->mtx.lock();	
				if(exe->topological_sort_list.size()==0){
					exe->mtx.unlock();
					return;
					//sleep					// sleep->
				}
				else{
					Task* new_task = exe->topological_sort_list[exe->topological_sort_list.size()-1];
					exe->topological_sort_list.pop_back();
					if(new_task->dependency>0){
						exe->topological_sort_list.push_back(new_task);
						exe->mtx.unlock();	
						unique_lock<mutex> lck(exe->cv_mtx);
						exe->cond_var.wait(lck);
						//sleep
					}
					else{
						exe->mtx.unlock();
						new_task->execute_task();
						for(auto suc_task: new_task->successor){
							suc_task->dependency--;
						}
						unique_lock<mutex> lck(exe->cv_mtx);
						// cout<<"Notify them stupid\n";
						exe->cond_var.notify_all();
						// notify all
					}
					
				}



			} while(flag!=false);
			// function execute
			// dependency remove
		};

		void start_threads(int num_of_threads){
			vector<thread> all_threads;
			for(int i=0;i<num_of_threads;i++){
				thread th(execute_thread, this);
				all_threads.push_back(move(th));
			}
			for(int i=0;i<num_of_threads;i++){
				all_threads[i].join();
			}
			exit(0);
		}

		void run(Taskflow taskflow){
			this->current_taskflow = taskflow;
			// graph build 
			this->build(taskflow);
			cout<<"Top list:";
			for(auto task: topological_sort_list){
				cout<<task->id<<" ";
			}
			cout<<"\n";
			// cout<<"Size after build"<<topological_sort_list[2]->successor.size()<<"\n";
			
			// algorith start -- threads
			int num_of_threads = NUMBER_OF_THREADS;
			this->start_threads(num_of_threads);

		}

};
