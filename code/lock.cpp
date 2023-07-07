#include <mutex>

::std::mutex
   mutex0,
   mutex1;

::std::timed_mutex
   mutex2;

int main(int argc, char ** argv)
{
   //
   // Mutexes do not need to be of the same type:
   //
   
   ::std::lock( mutex0, mutex1, mutex2 );
   
   mutex0.unlock();
   mutex1.unlock();
   mutex2.unlock();
   
   return 0;
}
