#include <vector>
#include <iostream>

#include <thread>
#include <mutex>

::std::vector
   <
   unsigned
   >
   data;

::std::mutex
   mutex;

void load_data(unsigned value)
{
   //
   // Sleep briefly, then upload a value to 'data':
   //
   
   ::std::this_thread::sleep_for 
      (
      ::std::chrono::seconds(1)
      )
      ;
   
   //
   // Lock the mutex:
   //
   
   ::std::lock_guard
      <
      ::std::mutex
      >
      guard(mutex);
   
   data.push_back
      (
      value
      )
      ;
   
   //
   // The mutex is automatically unlocked here:
   //
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::vector
      <
      ::std::thread
      >
      threads;
   
   //
   // Start 10 threads, each with a different value to
   // insert into 'data':
   //
   
   for(unsigned i = 0; i< 10; ++i)
   {
      threads.push_back
         (
         ::std::thread( load_data, i )
         )
         ;
   }
   
   for(unsigned i = 0; i< 10; ++i)
   {
      threads[i].join();
   }
   
   //
   // Display the contents of 'data':
   //
   
   for( auto const & datum : data )
   {
      ::std::cout << datum << " ";
   }
   ::std::cout << ::std::endl;
   
   return 0;
}
