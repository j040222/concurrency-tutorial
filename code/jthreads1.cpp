#include <iostream>

#include <thread>

void worker
   (
   ::std::stop_token
      stop
         ,
   unsigned
      thread_id
   )
{
   unsigned
      index = 0u;
   
   while
      (
         //
         // Continue until request_stop is called:
         //
      not stop.stop_requested()
      )
   {
      ::std::cout << index++ << " ";
      
      ::std::cout.flush();
      
      ::std::this_thread::sleep_for
         (
         ::std::chrono::seconds(1)
         )
         ;
   }
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::jthread
      thread( worker, 0u );
   
   ::std::this_thread::sleep_for
      (
      ::std::chrono::milliseconds(5100)
      )
      ;
   
   thread.request_stop();           // Request stop
   
   ::std::cout << ::std::endl;
   
   return 0;
}
