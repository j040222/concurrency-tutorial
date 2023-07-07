#include <vector>
#include <iostream>

#include <thread>
#include <mutex>
#include <memory>

struct Node final
{
   ::std::vector
      <
      unsigned
      >
      links;
   
   ::std::shared_ptr
      <
      ::std::mutex
      >
      mutex;
   
   Node(void)
      :
      mutex
         (
         ::std::make_shared
            <
            ::std::mutex
            >
            ()
         )
      { }
};

::std::vector
   <
   Node
   >
   nodes;

void link_two_nodes(unsigned i, unsigned j)
{
   //
   // Lock the mutexes in both nodes:
   //
   
   ::std::scoped_lock
      guard
         (
         *nodes[i].mutex
            ,
         *nodes[j].mutex
         )
         ;
   
   //
   // Modify the nodes:
   //
   
   nodes[i].links.push_back( j );
   nodes[j].links.push_back( i );
   
   return;
}

int main(int argc, char ** argv)
{
   ::std::vector
      <
      ::std::thread
      >
      threads;
   
   for(unsigned i = 0; i< 6; ++i)
   {
      nodes.emplace_back();
   }
   
   //
   // Start many threads, each of which inserts a different
   // link between nodes:
   //
   
   for(unsigned i = 0; i< nodes.size(); ++i)
   {
      for(unsigned j = (i + 1); j< nodes.size(); j+=2)
      {
         threads.push_back
            (
            ::std::thread(link_two_nodes, i, j)
            )
            ;
      }
   }
   
   for(auto & thread : threads)
   {
      thread.join();
   }
   
   for(unsigned i = 0; i< nodes.size(); ++i)
   {
      ::std::cout << "Node "
                  << i
                  << " is linked to: "
                     ;
      
      for(auto const & record : nodes[i].links)
      {
         ::std::cout << record << " ";
      }
      
      ::std::cout << ::std::endl;
   }
   
   return 0;
}
