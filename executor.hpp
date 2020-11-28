#include <bits/stdc++.h>
#include "taskflow.hpp"

using namespace std;



class Executor {
	// friend class task;
	// friend class taskflow;
	public:
		Executor(){};
		mutex mtx, cv_mtx;
		condition_variable cond_var;
		// Taskflow current_taskflow;
		vector<Task*> task_list;
		int total_task=0; 


		static void execute_thread(Executor* exe){
			bool flag=true;
			do {
				exe->mtx.lock();	
				if(exe->task_list.size()==0){
					exe->mtx.unlock();
					return;
					//sleep					// sleep->
				}
				else{
					Task* new_task = exe->task_list[exe->task_list.size()-1];
					exe->task_list.pop_back();
					if(new_task->dependency>0){
						exe->task_list.push_back(new_task);
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
			return;
		}

		void run(vector<Taskflow> taskflow_list){
			// graph build
			for(auto current_taskflow: taskflow_list){
				current_taskflow.build();
				for(Task* task: current_taskflow.topological_sort_list){
					task_list.push_back(task);
					total_task++;
				}
			} 
			// cout<<"Top list:";
			// for(auto task: task_list){
			// 	cout<<task->id+1<<" ";
			// }
			// cout<<"\n";
			// cout<<"Size after build"<<task_list[2]->successor.size()<<"\n";
			
			// algorith start -- threads
			int num_of_threads = NUMBER_OF_THREADS;
			this->start_threads(num_of_threads);

		}

};
