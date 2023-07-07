#include <iostream>
#include <algorithm>
#include <vector>

#include <future>
#include <thread>

void find_largest
   (
   ::std::vector <int> const &
      values
         ,
   ::std::promise <int>
      maximum
   )
{
   maximum.set_value
      (
      *::std::max_element
         (
         values.begin()
            ,
         values.end()
         )
      )
      ;
}

int main(int argc, char ** argv)
{
   ::std::vector <int> const
      values = { 1, 2, 3, 4, 5 };
   
   ::std::promise <int>
      maximum;
   
   ::std::future <int>
      future = maximum.get_future();
   
   ::std::jthread
      worker
         (
         find_largest,
         ::std::ref(values),
         ::std::move(maximum)
         )
         ;
   
   ::std::cout << "Maximum Value: "
               << future.get()
               << ::std::endl
                  ;
   
   return 0;
}
