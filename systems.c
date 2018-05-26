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
     .hostinfo = "Neural Implant - Home Edition V4.5663.4A",
     .filesystem =
         { .num_files = 3, 
            .files[0] = { "README", "Help information", "rw-r--r--", 1 },
            .files[1] = { "bitcoin", "100", "rw-rw-rw-", 1 },
            .files[2] = { "tasks", "quest information", "rw-r--r--", 1 },
         },
   },
   { .ip_address = "10.0.0.1",
     .hostinfo = "Test host info",
      .filesystem = {},
   },
};

int current_system = 0;


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
void host_command( args *arguments );
void ls_command( args *arguments );

#define MAX_COMMANDS 3

commands command_list[ MAX_COMMANDS ] = {
   { "help", "Get help about available system commands.", help_command },
   { "host", "Get info on the current host.", host_command },
   { "ls",   "List the files on the current host.", ls_command },
};

void help_command( args *arguments )
{
   char line[MAX_MSG_SIZE];

   for ( int i = 0 ; i < MAX_COMMANDS ; i++ )
   {
      sprintf( line, "%s | %s", 
               command_list[ i ].name, command_list[ i ].help );
      add_message( line );
   }
}

void host_command( args *arguments )
{
   char line[MAX_MSG_SIZE];

   sprintf( line, "%s (%s)", systems[ 0 ].hostinfo, systems[ 0 ].ip_address );

   add_message( line );

   return;
}

void ls_command( args *arguments )
{
   char line[MAX_MSG_SIZE];

   for ( int i = 0 ; i < systems[0].filesystem.num_files ; i++ )
   {
      sprintf( line, "%s %5u %-17s (%d)", 
               systems[0].filesystem.files[i].attributes,
               (unsigned int)strlen( systems[0].filesystem.files[i].contents),
               systems[0].filesystem.files[i].filename,
               systems[0].filesystem.files[i].quantity );

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


