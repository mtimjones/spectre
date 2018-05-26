#include "headers.h"
#include "systems.h"
#include <ctype.h>

#define MAX_ARGS    3

typedef struct
{
   int  num_args;
   char *args[ MAX_ARGS ];
} args;

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


void parse_args( char *line, args *arguments )
{
   arguments->num_args = 0;

   while ( *line != 0 )
   {
      // Skip leading white space.
      while ( isspace( *line ) && ( *line != 0 ) ) line++;
      
      // If at the end of line, return
      if ( *line == 0 ) return;

      // We're at non-white-space, so record this argument.
      arguments->args[ arguments->num_args++ ] = line;

      // Skip this argument.
      while ( *line != ' ' && *line != 0 ) line++;

      // We've found a space, drop a NULL and step to the next char.
      if ( *line == ' ' ) *line++ = 0;

      // If we have MAX_ARGS arguments, just return.
      if ( arguments->num_args == MAX_ARGS ) return;
   }

   return;
}

typedef void (*command)( args *arguments );

#define MAX_COMMAND_SIZE   12
#define MAX_HELP_SIZE      50

#define MAX( a, b ) ( ( (a) > (b) ) ? (a) : (b) )

typedef struct
{
   char    name[ MAX_COMMAND_SIZE ];
   char    help[ MAX_HELP_SIZE ];
   command function;
} commands;

void help_command( args *arguments );

#define MAX_COMMANDS 1

commands command_list[ MAX_COMMANDS ] = {
   { "help", "Get help about available system commands.", help_command },
};

void help_command( args *arguments )
{
   char line[80];

   for ( int i = 0 ; i < MAX_COMMANDS ; i++ )
   {
      sprintf( line, "%s | %s", 
               command_list[ i ].name, command_list[ i ].help );
      add_message( line );
   }
}


void system_command( args *arguments )
{
   for ( int i = 0 ; i < MAX_COMMANDS ; i++ )
   {
      int size = MAX( strlen( arguments->args[ 0 ] ), 
                      strlen( command_list[ i ].name ) );

      if ( strncmp( arguments->args[ 0 ], command_list[ i ].name, size ) == 0 )
      {
         ( command_list[ i ].function )( arguments );
         return;
      }
   }

   add_message( "Unknown command." );

   return;
}


void system_exec( char* line )
{
   args arguments = {0, (char*)0, (char*)0, (char*)0};

   parse_args( line, &arguments );

   system_command( &arguments );

   return;
}


