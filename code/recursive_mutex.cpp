#include <iostream>
#include <mutex>
#include <thread>

::std::recursive_mutex
   mutex;

void function0(void)
{
   ::std::lock_guard
      <
      ::std::recursive_mutex
      >
      lock(mutex);            // Does not block
}

void function1(void)
{
   ::std::lock_guard
      <
      ::std::recursive_mutex
      >
      lock(mutex);
   
   function0();
}

int main(int argc, char ** argv)
{
   ::std::jthread( function1 );
   
   return 0;
}
