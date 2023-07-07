#include <iostream>
#include <syncstream>

#include <thread>
#include <vector>
#include <barrier>

void when_done(void) noexcept
{
   ::std::cout << "Done"
               << ::std::endl
                  ;
}

unsigned const
   number_of_threads = 5u;

::std::barrier
   barrier(number_of_threads, when_done);

void do_work(void)
{
   ::std::osyncstream(::std::cout) << "Before Barrier"
                                   << ::std::endl
                                      ;
   
   barrier.arrive_and_wait();
   
   ::std::osyncstream(::std::cout) << "Stage 1"
                                   << ::std::endl
                                      ;
   
   //
   // Reuse the barrier:
   //
   
   barrier.arrive_and_wait();
   
   ::std::osyncstream(::std::cout) << "After Barrier"
                                   << ::std::endl
                                      ;
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
   
   //
   // 10 threads have completed 'do_work'
   //
   
   return 0;
}
