#include <iostream>
#include <future>

int do_work(void)
{
   return 42;
}

int main(int argc, char ** argv)
{
   auto
      future =
         ::std::async( std::launch::deferred, do_work );
   
   ::std::cout << future.get() // do_work is evaluated here
               << ::std::endl
                  ;
   
   return 0;
}
