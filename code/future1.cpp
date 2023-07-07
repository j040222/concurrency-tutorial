#include <iostream>
#include <future>
#include <thread>

int main(int argc, char ** argv)
{
   //
   // Get a future from a promise object:
   //
   
   ::std::promise <int>
      promise;
   
   ::std::future <int>
      future = promise.get_future();
   
   ::std::jthread
      thread( [&promise] { promise.set_value( 42 ); } );
   
   future.wait();
   
   ::std::cout << future.get() << ::std::endl;
   
   return 0;
}
