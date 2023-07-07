#include <vector>
#include <iostream>

#include <thread>
#include <mutex>
#include <memory>

::std::mutex
   mutex;

int main(int argc, char ** argv)
{
   //
   // unique_lock differs from lock_guard in that
   // unique_lock contains member functions for:
   //    (a) locking and try-locking the underlying mutex;
   //    (b) unlocking it;
   //    (c) testing whether or not the mutex was locked
   //        by itself;
   //    (d) disassociating the mutex without unlocking it.
   //
   
   {
   
   //
   // Lock the mutex:
   //
   
   ::std::unique_lock
      <
      ::std::mutex
      >
      guard(mutex);
   
   }
   
   {
   
   //
   // Defer locking of the mutex:
   //
   
   ::std::unique_lock
      <
      ::std::mutex
      >
      guard(mutex, ::std::defer_lock);
   
   guard.lock();
   
   guard.unlock();   // Also releases ownership
   
   }
   
   {
   
   //
   // Try to lock a timed mutex for 2 seconds:
   //
   
   ::std::timed_mutex
      mutex;
   
   ::std::unique_lock
      <
      ::std::timed_mutex
      >
      guard(mutex, ::std::defer_lock);
   
   guard.try_lock_for
      (
      ::std::chrono::seconds(2)
      )
      ;
   
   }
   
   {
   
   ::std::unique_lock
      <
      ::std::mutex
      >
      guard(mutex);
   
   //
   // Release the mutex without unlocking it:
   //
   
   guard.release();
   
   mutex.unlock();
   
   }
   
   {
   
   ::std::unique_lock
      <
      ::std::mutex
      >
      guard(mutex, ::std::defer_lock);
   
   //
   // Test whether or not the guard owns the lock:
   //
   
   ::std::cout << ( guard.owns_lock() ? "" : "Not " )
               << "Locked"
               << ::std::endl;
                     // Reads 'Not Locked'
   
   guard.lock();
   
   ::std::cout << ( guard.owns_lock() ? "" : "Not " )
               << "Locked"
               << ::std::endl;
                     // Reads 'Locked'
   
   }
   
   return 0;
}
