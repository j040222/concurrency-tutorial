#include <iostream>
#include <mutex>
#include <thread>

::std::once_flag
   once;

void worker(unsigned thread_id)
{
   ::std::call_once
      (
      once,
      [&thread_id]
      {
         ::std::cout << "Thread "
                     << thread_id
                     << " did the work"
                     << ::std::endl;
      }
      )
      ;
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::jthread( worker, 0u );
   ::std::jthread( worker, 1u );
   ::std::jthread( worker, 2u );
   ::std::jthread( worker, 3u );
   
   return 0;
}
