#include "headers.h"
#include "systems.h"
#include <ctype.h>

system_t systems[ 2 ] = { 
   { .ip_address = "127.0.0.1",
      .filesystem =
         { .num_files = 2, 
            .files[0] = { "README", "Help information\n", 1 },
            .files[1] = { "bitcoin", "100\n", 1 },
         },
   },
   { .ip_address = "10.0.0.1",
      .filesystem = {},
   },
};


void system_exec( char* line )
{
   int  args = 0;
   char *arg[3];

   while ( isspace( *line ) && ( *line != 0 ) ) line++;

   if ( *line == 0 ) return;

   

   return;
}


