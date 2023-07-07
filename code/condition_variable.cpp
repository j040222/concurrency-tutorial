#include <iostream>
#include <syncstream>

#include <mutex>
#include <thread>
#include <condition_variable>

::std::mutex
   mutex0,
   mutex1;

::std::condition_variable
   condition,
   worker_is_done;

bool
   is_ready = false,
   is_finished = false;

::std::string
   content = "Initial Content";

void function(unsigned thread_index)
{
   ::std::unique_lock
      lock
         (
         mutex0
         )
         ;
   
   condition.wait
      (
      lock,
      []
         {
            return
               is_ready;
         }
      )
      ;
   
   ::std::osyncstream(::std::cout) << "Worker thread "
                                   << thread_index
                                   << " is active"
                                   << ::std::endl
                                      ;
   
   //
   // Use another condition variable to notify the parent
   // thread that this thread is done:
   //
   
   {
   
   ::std::lock_guard
      lock
         (
         mutex1
         )
         ;
   
   is_finished = true;
   
   worker_is_done.notify_one();
   
   }
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::jthread worker0( function, 0u );
   ::std::jthread worker1( function, 1u );
   ::std::jthread worker2( function, 2u );
   ::std::jthread worker3( function, 3u );
   
   {
   
   ::std::lock_guard
      lock
         (
         mutex0
         )
         ;
   
   is_ready = true;
   
   }
   
   ::std::osyncstream(::std::cout) << "Notify one thread..."
                                   << ::std::endl
                                      ;
   
   condition.notify_one();
   
   //
   // Wait to be notified that the child thread is done:
   //
   
   {
   
   ::std::unique_lock
      lock
         (
         mutex1
         )
         ;
   
   worker_is_done.wait
      (
      lock,
      []
         {
            return
               is_finished;
         }
      )
      ;
   
   is_finished = false;
   
   }
   
   ::std::osyncstream(::std::cout) << "Notify one thread..."
                                   << ::std::endl
                                      ;
   
   condition.notify_one();
   
   //
   // Wait to be notified that the child thread is done:
   //
   
   {
   
   ::std::unique_lock
      lock
         (
         mutex1
         )
         ;
   
   worker_is_done.wait
      (
      lock,
      []
         {
            return
               is_finished;
         }
      )
      ;
   
   is_finished = false;
   
   }
   
   ::std::osyncstream(::std::cout) << "Notify all "
                                      "remaining threads..."
                                   << ::std::endl
                                      ;
   
   //
   // Unblock all remaining threads:
   //
   
   condition.notify_all();
   
   return 0;
}
