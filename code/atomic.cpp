#include <iostream>
#include <vector>

#include <atomic>
#include <thread>

int main(int argc, char ** argv)
{
   {
   
   ::std::atomic <int>
      atomic( 42 );
   
   atomic.store( 43 );
   
   auto
      value_stored = atomic.load();
   
   //
   // Alternatively:
   //
   
   value_stored = (int) atomic;
   
   ::std::cout << value_stored               // 43
               << ::std::endl
                  ;
   
   //
   // Exchange the stored value and get the previous value:
   //
   
   value_stored = atomic.exchange( 42 );
   
   ::std::cout << atomic                     // 42
               << ::std::endl
                  ;
   
   }
   
   //
   // There are many type aliases and specializations for
   // integer (and boolean and char) atomic types:
   //
   
   {
   
   ::std::atomic_uint32_t
      atomic;
   
   atomic.fetch_xor( (uint32_t)1 ); // Perform XOR on the
                                    // stored value, and
                                    // return the value held
                                    // previously.
   
   }
   
   //
   // Multiple threads can modify an atomic simultaneously,
   // whereas only one should modify a non-atomic at a time:
   //
   
   {
   
   ::std::atomic_uint
      atomic_counter(0u);
   unsigned
      nonatomic_counter(0u);
   
   {
   
   ::std::vector
      <
      ::std::jthread
      >
      threads;
   
   auto
      function =
      [&] (void)
      {
         for( unsigned i(0u); i< 1000u; ++i )
         {
            ++atomic_counter;
               //
               // Multiple concurrent increments may only
               // increment nonatomic_counter by 1:
               //
            ++nonatomic_counter;
         }
      }
      ;
   
   for( int i(0); i< 10u; ++i )
   {
      threads.emplace_back( function );
   }
   
   }
   
   ::std::cout << "Counter with atomics: "
               << atomic_counter
               << ::std::endl
               << "Without atomics: "
               << nonatomic_counter
               << ::std::endl
                  ;
   
   }
   
   {
   
   //
   // C++11 also contains many free functions that modify
   // atomics:
   //
   
   ::std::atomic_uint
      atomic;
   
   ::std::atomic_store( &atomic, 42u );
   
   atomic = 1u;
   
   unsigned
      stored_value = ::std::atomic_load( &atomic );
   
   stored_value =
      ::std::atomic_fetch_add( &atomic, 1u );
   
   }
   
   return 0;
}
