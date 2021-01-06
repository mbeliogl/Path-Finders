#include <stdio.h>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <queue>

#include <mutex>

using namespace std;

void takeJobs(int threadNum, queue<int>* jobQueue, mutex* jobLock)
{
   while (1){

      jobLock->lock(); 
      if (!jobQueue->empty())
      {
	 int jobLength = jobQueue->front();
	 jobQueue->pop();
	 printf("%i took a job of length %i. Number of jobs left: %i\n", threadNum, jobLength, (int)jobQueue->size());
     
     jobLock->unlock();
	 this_thread::sleep_for(std::chrono::seconds(jobLength));
	 printf("%i finished its job.\n", threadNum);
      }
      else{
         jobLock->unlock();
      }
   }
}

void makeJobs(int threadNum, queue<int>* jobQueue, mutex* jobLock)
{
   while (1)
   {
      int jobLength = rand()%5 + 1;
      jobQueue->push(jobLength);
      printf("%i created a job of length %i. Number of jobs left: %i\n", threadNum, jobLength, (int)jobQueue->size());
	 this_thread::sleep_for(std::chrono::seconds(1));
   }
}

int main(int argc, char** argv)
{
   int numConsumers = 1;
   if(argc > 1)
   {
      numConsumers = atoi(argv[1]);
   }
   queue<int> jobQueue;

   mutex jobLock;

   thread producer = thread(makeJobs, 0, &jobQueue, &jobLock);

   thread* consumers = new thread[numConsumers];
   for(int i = 0; i < numConsumers; i++)
   {
      consumers[i] = thread(takeJobs, i + 1, &jobQueue, &jobLock);
   }

   producer.join();
   for(int i = 0; i < numConsumers; i++)
   {
      consumers[i].join();
   }
}
