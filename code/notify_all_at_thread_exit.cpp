#include <condition_variable>
#include <mutex>
#include <thread>

::std::mutex
   mutex;

::std::condition_variable
   condition;

bool
   is_ready = false;

void worker()
{
   struct Object { };
   
   thread_local Object
      object;
   
   ::std::unique_lock
      lock
         (
         mutex
         )
         ;
   
   is_ready = true;
   
   ::std::notify_all_at_thread_exit
      (
      condition
         ,
      ::std::move( lock )
      )
      ;
   
   //
   // Destroy 'object'
   //
   
   //
   // condition.notify_all() now happens automatically.
   //
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::jthread
      thread( worker );
   
   thread.detach();
   
   //
   // Wait to be notified of the worker thread terminating:
   //
   
   ::std::unique_lock
      lock
         (
         mutex
         )
         ;
   
   condition.wait
      (
      lock,
      [] (void) { return is_ready; }
      )
      ;
   
   return 0;
}
