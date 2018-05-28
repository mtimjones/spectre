#include "headers.h"

system_stack_t system_stack;

void init_system( int system )
{
   system_stack.top_index = 0;
   push_system( system );
}

int current_system( void )
{
   return system_stack.entry[ system_stack.top_index - 1 ];
}

void push_system( int system )
{
   system_stack.entry[ system_stack.top_index++ ] = system;
}

int pop_system( void )
{
   return system_stack.entry[ --system_stack.top_index ];
}

