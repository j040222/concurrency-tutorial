#include <iostream>
#include <mutex>
#include <thread>

::std::timed_mutex
   mutex;

void function(unsigned thread_index)
{
   auto const
      time_now = ::std::chrono::steady_clock::now();
   
   if (
         mutex.try_lock_until
            (
            time_now + ::std::chrono::seconds(1)
            )
      )
   {
      ::std::this_thread::sleep_for
         (
         ::std::chrono::seconds(2)
         )
         ;
      
      mutex.unlock();
   }
   else
   {
      ::std::cout << "Thread "
                  << thread_index
                  << " was excluded"
                  << ::std::endl
                     ;
   }
}

int main(int argc, char ** argv)
{
   ::std::jthread(function, 0u);
   ::std::jthread(function, 1u);
   
   return 0;
}
