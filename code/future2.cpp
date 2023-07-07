#include <iostream>
#include <future>
#include <thread>

int main(int argc, char ** argv)
{
   //
   // Get a future from ::std::async:
   //
   
   ::std::future <int>
      future =
         ::std::async
            (
            ::std::launch::async,
            [] (void) { return 42; }
            )
            ;
   
   future.wait();
   
   ::std::cout << future.get() << ::std::endl;
   
   return 0;
}
