#include <iostream>
#include <exception>

#include <mutex>
#include <thread>

::std::once_flag
   once;

void worker(unsigned thread_id, bool do_raise_exception)
{
   try
   {
      ::std::call_once
         (
         once,
         [&]
         {
            //
            // Raise an exception if do_raise_exception
            // is true, otherwise return normally:
            //
            
            if (
                  do_raise_exception
               )
            {
               ::std::cout << "Thread "
                           << thread_id
                           << " raised an exception"
                           << ::std::endl;
               
               throw ::std::runtime_error("error");
               
               return;
            }
            
            ::std::cout << "Thread "
                        << thread_id
                        << " did the work"
                        << ::std::endl;
         }
         )
         ;
   }
   catch( ... )
   {
   }
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::jthread( worker, 0u, true );
   ::std::jthread( worker, 1u, true );
   ::std::jthread( worker, 2u, false );
   ::std::jthread( worker, 3u, true );
   
   return 0;
}
