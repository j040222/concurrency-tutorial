#include <iostream>
#include <syncstream>

#include <semaphore>
#include <thread>
#include <vector>

::std::counting_semaphore<3u>
   semaphore(3u);

void function(unsigned thread_index)
{
   semaphore.acquire();
   
   //
   // Only 3 threads are allowed in this section at a time:
   //
   
   ::std::osyncstream(::std::cout)
      << "Thread "
      << thread_index
      << " is in the critical section"
      << ::std::endl
         ;
   
   ::std::this_thread::sleep_for
      (
      ::std::chrono::seconds(3)
      )
      ;
   
   semaphore.release();
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::vector
      <
      ::std::jthread
      >
      threads;
   
   unsigned const
      number_of_threads(10);
   
   for(unsigned i(0u); i< number_of_threads; ++i)
   {
      threads.emplace_back( function, i );
      
      continue;
   }
   
   return 0;
}
