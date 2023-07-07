#include <chrono>

#include <atomic>
#include <thread>

int main(int argc, char ** argv)
{
   ::std::atomic_int
      atomic(42);
   
   ::std::jthread
      thread
         (
            [&atomic] (void)
            {
               ++atomic;
               
               ::std::this_thread::sleep_for
                  (
                  ::std::chrono::seconds(3)
                  )
                  ;
               
               atomic.notify_one();
            }
         )
         ;
   
   atomic.wait(42);                 // Waits for notify_one
   
   return 0;
}
