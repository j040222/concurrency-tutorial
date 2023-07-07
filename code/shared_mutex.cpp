#include <iostream>
#include <syncstream>

#include <shared_mutex>
#include <thread>
#include <vector>

::std::shared_mutex
   mutex;

::std::string
   content = "Initial Content";

void reader(unsigned thread_index)
{
   mutex.lock_shared();
   
   ::std::osyncstream(::std::cout) << "Thread "
                                   << thread_index
                                   << " read: \""
                                   << content
                                   << "\""
                                   << ::std::endl
                                      ;
   
   mutex.unlock_shared();
   
   return;
}

void modify_content(void)
{
   mutex.lock();
   
   content = "Modified Content";
   
   ::std::osyncstream(::std::cout) << "Writer modified "
                                      "content"
                                   << ::std::endl
                                      ;
   
   mutex.unlock();
   
   return;
}

int main(int argc, char ** argv)
{
   //
   // Create 10 reader threads and one writer thread:
   //
   
   ::std::vector
      <
      ::std::jthread
      >
      readers;
   
   unsigned const
      number_of_threads = 10u;
   
   for(unsigned i(0u); i< number_of_threads; ++i)
   {
      readers.push_back
         (
         ::std::jthread( reader, i )
         )
         ;
   }
   
   ::std::jthread
      writer(modify_content);
   
   return 0;
}
