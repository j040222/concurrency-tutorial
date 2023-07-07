#include <iostream>
#include <syncstream>

#include <thread>

void task
   (
   ::std::stop_token
      stop_token
   )
{
   while
      (
         not stop_token.stop_requested()
      )
   {
      ::std::this_thread::sleep_for
         (
         ::std::chrono::seconds(1)
         )
         ;
   }
   
   ::std::osyncstream(::std::cout) << "Thread "
                                   << ::std::
                                         this_thread::
                                            get_id()
                                   << " stopped"
                                   << ::std::endl
                                      ;
}

int main(int argc, char ** argv)
{
   ::std::jthread
      thread( task );
   
   ::std::this_thread::sleep_for
      (
      ::std::chrono::seconds(3)
      )
      ;
   
   ::std::stop_callback
      callback
         (
         thread.get_stop_token(),
         [] (void)
            {
               ::std::osyncstream(::std::cout)
                  << "Thread "
                  << ::std::this_thread::get_id()
                  << " callback"
                  << ::std::endl
                     ;
            }
         )
         ;
   
   //
   // Stop the thread:
   //
   
   thread.request_stop();
   
   return 0;
}
