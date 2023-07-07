#include <iostream>
#include <future>

int do_work(void)
{
   return 42;
}

int main(int argc, char ** argv)
{
   auto
      future = ::std::async( std::launch::async, do_work );
   
   future.wait();
   
   ::std::cout << future.get() << ::std::endl;
   
   return 0;
}
