#include <syncstream>
#include <iostream>

#include <thread>
#include <shared_mutex>
#include <memory>
#include <vector>

::std::shared_mutex
   mutex;

::std::string
   content = "Initial Content";

//
// Read the content:
//

void read_action(unsigned reader_index)
{
   ::std::shared_lock
      <
      ::std::shared_mutex
      >
      lock
         (
         mutex
         )
         ;
   
   ::std::osyncstream(::std::cout) << "Reader "
                                   << reader_index
                                   << " reads: \""
                                   << content
                                   << "\""
                                   << ::std::endl
                                      ;
}

//
// Modify (write to) the content:
//

void write_action(void)
{
   ::std::lock_guard
      <
      ::std::shared_mutex
      >
      lock
         (
         mutex
         )
         ;
   
   content = "Modified Content";
   
   ::std::osyncstream(::std::cout) << "Writer wrote: \""
                                   << content
                                   << "\""
                                   << ::std::endl
                                      ;
}

int main(int argc, char ** argv)
{
   //
   // Create multiple content readers and only 1 writer:
   //
   
   ::std::vector
      <
      ::std::thread
      >
      reader_threads;
   
   ::std::unique_ptr
      <
      ::std::thread
      >
      writer_thread;
   
   ::std::size_t
      number_of_threads(10u);
   
   reader_threads.reserve( number_of_threads );
   
   for(unsigned i(0u); i< number_of_threads; ++i)
   {
      reader_threads.push_back
         (
         ::std::thread(read_action, i)
         )
         ;
   }
   
   writer_thread =
      ::std::make_unique
         <
         ::std::thread
         >
         (
         write_action
         )
         ;
   
   for(auto & thread : reader_threads)
   {
      thread.join();
   }
   
   writer_thread->join();
   
   return 0;
}
