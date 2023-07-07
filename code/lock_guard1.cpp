#include <mutex>

::std::mutex
   mutex0,
   mutex1;

int main(int argc, char ** argv)
{
   {
   
   mutex0.lock();
   
   //
   // Acquire the existing lock on mutex0:
   //
   
   ::std::lock_guard
      <
      ::std::mutex
      >
      guard
         (
         mutex0,
         ::std::adopt_lock
         )
         ;
   
   //
   // mutex0 is unlocked here:
   //
   
   }
   
   {
   
   //
   // Adopt 2 locks locked by ::std::lock (which uses a
   // deadlock avoidance algorithm to avoid deadlock):
   //
   
   ::std::lock(mutex0, mutex1);
   ::std::lock_guard
      <
      ::std::mutex
      >
      guard0
         (
         mutex0,
         ::std::adopt_lock
         )
         ;
   ::std::lock_guard
      <
      ::std::mutex
      >
      guard1
         (
         mutex1,
         ::std::adopt_lock
         )
         ;
   
   }
   
   return 0;
}
