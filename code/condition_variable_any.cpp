#include <condition_variable>
#include <mutex>

::std::mutex
   mutex;

::std::condition_variable_any
   condition;

bool
   is_ready = true;

int main(int argc, char ** argv)
{
   condition.wait
      (
      mutex,
      [] (void) { return is_ready; }
      )
      ;
   
   return 0;
}
