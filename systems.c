#include "headers.h"
#include "systems.h"
#include "commands.h"
#include <ctype.h>

system_t systems[ NUM_SYSTEMS ] = { 
   { 
      .ip_address = "127.0.0.1",
      .hostinfo = "Neural Implant - Home Edition V4.5663.4A",
      .flags = {
         .Timezone = 0,
         .Probeable = 1,
         .Discoverable = 1,
      },
      .filesystem = { 
            .num_files = 4, 
            .files[0] = 
               // 1234567890123456789012345678901234567890123456789012345678
               {  "README", 
                   "CyberOS README\n"
                   "Type help for command information.\n"
                   "WARNING: you are required to follow all laws under the\n"
                   "IT ACT of 2064.  Crimes against people, property, or the\n"
                   "Government are punishable by death.\n",
                  .attributes = "rw-r--r--", 
                  .quantity = 1 },
            .files[1] = { 
                  "bitcoin", 
                   "100\n", 
                  "rw-rw-rw-", 
                  .quantity = 1 },
            .files[2] = { 
                  "tasks", 
                   "quest information\n", 
                  "rw-r--r--", 
                  .quantity = 1 },
            .files[3] = {
                  "tracer",
                   "Trace hosts from this system.\n"
                   "InstallTime: 3\n"
                   "RunTime: 2\n",
                  "rwxrwxrwx", 
                  .quantity = 1 },
      },
      .processes = {
         .num_processes = 2,
         .process[0] = {
            .name = "CyberOS uKernel",
            .pid = 1335,
            .strength = 15,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .Active = 1,
               .Killable = 0,
            },
         },
         .process[1] = {
            .name = "Sentry",
            .pid = 6168,
            .strength = 20,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .Active = 1,
               .Killable = 1,
            },
         },
      },
   },

   { .ip_address = "10.0.0.1",
     .hostinfo = "Test host info",
     .filesystem = {},
      .flags = {
         .Timezone = 300,
         .Probeable = 0,
         .Discoverable = 0,
      },
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


