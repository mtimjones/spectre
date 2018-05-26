#include "headers.h"
#include "systems.h"
#include <ctype.h>
#include "commands.h"

void help_command( args *arguments );
void host_command( args *arguments );
void ls_command( args *arguments );

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
      sprintf( line, "%-12s | %s", 
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

