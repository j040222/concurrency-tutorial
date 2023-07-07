#include <iostream>
#include <syncstream>

#include <thread>
#include <vector>
#include <latch>

unsigned const
   number_of_threads = 10u;

::std::latch
   work_done(number_of_threads);

void do_work(void)
{
   //
   // Decrement 'work_done' and wait until it reaches zero:
   //
   
   work_done.arrive_and_wait();
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::vector
      <
      ::std::jthread
      >
      threads;
   
   for(unsigned i(0u); i< number_of_threads; ++i)
   {
      threads.emplace_back( do_work );
      
      continue;
   }
   
   work_done.wait();
   
   //
   // 10 threads have completed 'do_work'
   //
   
   return 0;
}
