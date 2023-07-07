#include <iostream>

#include <thread>

void task(unsigned thread_id)
{
}

struct Callable final
{
   void operator() (void)
   {
   }
}
;

int main(int argc, char ** argv)
{
   {
   
   ::std::thread
      thread( task, 0u );
   
   //
   // Get the ID of the thread:
   //
   
   ::std::cout << "Thread ID: "
               << thread.get_id()
               << ::std::endl
                  ;
   
   thread.join();
   
   }
   
   {
   
   Callable
      object;
   
   ::std::thread
      thread( object );
   
   thread.join();
   
   }
   
   {
   
   ::std::thread
      thread( task, 2u );
   
   //
   // Get the ID of the thread:
   //
   
   ::std::cout << "Thread ID: "
               << thread.get_id()
               << ::std::endl
                  ;
   
   thread.detach();
   
   // thread.join();       // Throws ::std::system_error
   
   }
   
   {
   
   ::std::thread
      thread( task, 3u );
   
   ::std::cout << "Is jointable: "
               << thread.joinable()       // True
               << ::std::endl
                  ;
   
   thread.join();
   
   ::std::cout << "Is jointable: "
               << thread.joinable()       // False
               << ::std::endl
                  ;
   
   }
   
   return 0;
}
