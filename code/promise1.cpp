#include <iostream>
#include <algorithm>
#include <vector>

#include <future>
#include <thread>

void do_work
   (
   ::std::promise <void>
      signal
   )
{
   signal.set_value();
}

int main(int argc, char ** argv)
{
   ::std::promise <void>
      signal;
   
   auto
      future = signal.get_future();
   
   ::std::jthread
      worker
         (
         do_work,
         ::std::move(signal)
         )
         ;
   
   future.wait();
   
   return 0;
}
