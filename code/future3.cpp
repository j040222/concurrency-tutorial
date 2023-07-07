#include <iostream>
#include <syncstream>

#include <future>
#include <thread>

void
do_work
   (
   unsigned
      thread_index
         ,
   ::std::shared_future <void>
      future
   )
{
   future.wait();
   
   ::std::osyncstream(::std::cout) << "Thread "
                                   << thread_index
                                   << " worked"
                                   << ::std::endl
                                      ;
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::promise <void>
      is_ready;
   
   ::std::shared_future <void>
      future( is_ready.get_future() );
   
   ::std::jthread
      worker0( do_work, 0u, future ),
      worker1( do_work, 1u, future );
   
   is_ready.set_value();            // Activate both threads
   
   return 0;
}
