#include <iostream>
#include <cmath>
#include <functional>

#include <future>
#include <thread>

unsigned do_work(unsigned x, unsigned y)
{
   return std::pow(x, y);
}

int main(int argc, char ** argv)
{
   {
   
   ::std::packaged_task < unsigned( unsigned, unsigned ) >
      task( do_work );
   
   auto
      future = task.get_future();
   
   ::std::jthread
      thread( ::std::move( task ), 2, 3 );
   
   future.wait();
   
   ::std::cout << future.get()         // 2 ** 3 = 8
               << ::std::endl
                  ;
   
   }
   
   {
   
   //
   // Note that arguments can also be bound using
   // ::std::bind:
   //
   
   ::std::packaged_task < unsigned(void) >
      task
         (
         ::std::bind( do_work, 2, 3 )
         )
         ;
   
   auto
      future = task.get_future();
   
   ::std::jthread
      thread( ::std::move( task ) );   // No arguments
   
   future.wait();
   
   ::std::cout << future.get()         // 2 ** 3 = 8
               << ::std::endl
                  ;
   
   }
   
   return 0;
}
