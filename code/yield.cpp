#include <iostream>
#include <chrono>

#include <thread>

void worker
   (
   ::std::chrono::microseconds
      interval
   )
{
   auto const
      end_time =
         (
            interval
            +
            ::std::chrono::
               high_resolution_clock::now()
         )
         ;
   
   ::std::size_t
      number_of_loops = 0u;
   
   while
      (
         ::std::chrono::high_resolution_clock::now()
         <
         end_time
      )
   {
      ::std::this_thread::yield();
      
      ++number_of_loops;
   }
   
   ::std::cout << "Number of loops: "
               << number_of_loops
               << ::std::endl
                  ;
}

int main(int argc, char ** argv)
{
   ::std::jthread
      thread( worker, ::std::chrono::microseconds(10u) );
   
   return 0;
}
