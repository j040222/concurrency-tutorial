#include <thread>

void worker(unsigned thread_id)
{
   return;
}

int main(int argc, char ** argv)
{
   {
   
   ::std::jthread
      thread( worker, 0u );
   
   // thread.join() is automatically called by the dtor
   
   }
   
   return 0;
}
