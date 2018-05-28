#include "headers.h"

static system_stack_t system_stack;

static int cur_system;

void init_system( int system )
{
   system_stack.top_index = 0;
   cur_system = 0;
}

int current_system( void )
{
   return cur_system;
}

void set_current_system( int system )
{
   cur_system = system;
}

void push_system( int system )
{
   system_stack.entry[ system_stack.top_index++ ] = system;
}

int pop_system( void )
{
   return system_stack.entry[ --system_stack.top_index ];
}

