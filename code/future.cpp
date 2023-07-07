#include <iostream>
#include <future>
#include <thread>

int main(int argc, char ** argv)
{
   //
   // Get a future from a packaged task:
   //
   
   ::std::packaged_task < int (void) >
      task( [] (void) { return 42; } );
   
   ::std::future <int>
      future = task.get_future();
   
   ::std::jthread
      thread( ::std::move( task ) );
   
   future.wait();
   
   ::std::cout << future.get() << ::std::endl;
   
   return 0;
}
