#include <iostream>
#include <syncstream>

#include <thread>

void task
   (
   unsigned
      thread_id
         ,
   ::std::stop_source
      source
   )
{
   auto
      stop_token = source.get_token();
   
   while
      (
         not stop_token.stop_requested()
      )
   {
      ::std::this_thread::sleep_for
         (
         ::std::chrono::seconds(1)
         )
         ;
   }
   
   ::std::osyncstream(::std::cout) << "Thread "
                                   << thread_id
                                   << " stopped"
                                   << ::std::endl
                                      ;
}

int main(int argc, char ** argv)
{
   ::std::stop_source
      source;
   
   ::std::jthread t0( task, 0u, source );
   ::std::jthread t1( task, 1u, source );
   ::std::jthread t2( task, 2u, source );
   ::std::jthread t3( task, 3u, source );
   
   ::std::this_thread::sleep_for
      (
      ::std::chrono::seconds(5)
      )
      ;
   
   //
   // Stop all 4 threads:
   //
   
   source.request_stop();
   
   return 0;
}
