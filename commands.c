#include "headers.h"
#include "systems.h"
#include <ctype.h>
#include "commands.h"

void help_command( args *arguments );
void host_command( args *arguments );
void ls_command( args *arguments );
void cat_command( args *arguments );

commands command_list[ MAX_COMMANDS ] = {
   { "help", "Get help about available system commands.", help_command },
   { "host", "Get info on the current host.", host_command },
   { "ls",   "List the files on the current host.", ls_command },
   { "cat",  "Cat the contents of a file to the screen.", cat_command },
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

   sprintf( line, "%s (%s)", systems[ current_system ].hostinfo, 
               systems[ current_system ].ip_address );

   add_message( line );

   return;
}

void ls_command( args *arguments )
{
   char line[MAX_MSG_SIZE];

   for ( int i = 0 ; i < systems[ current_system ].filesystem.num_files ; i++ )
   {
      sprintf( line, "%s %5u %-17s (%d)", 
               systems[ current_system ].filesystem.files[i].attributes,
               (unsigned int)strlen( 
                  systems[ current_system ].filesystem.files[i].contents),
               systems[ current_system ].filesystem.files[i].filename,
               systems[ current_system ].filesystem.files[i].quantity );

      add_message( line );
   }
}


void cat_file( int file_index )
{
   char line[ MAX_MSG_SIZE ] = { 0 };
   char *file;
   int wrindex = 0, len;

   file = systems[ current_system ].
                        filesystem.files[ file_index ].contents;

   len = strlen( file );

   for ( int i = 0 ; i < len ; i++ )
   {
      if ( file[ i ] == '\n' )
      {
         line[ wrindex ] = 0;
         add_message( line );
         wrindex = 0;
         line[ 0 ] = 0;
      }
      else line[ wrindex++ ] = file[ i ];
   }
   
   return;
}

void cat_command( args *arguments )
{
   if ( arguments->num_args < 2 ) return;

   for ( int i = 0 ; i < systems[ current_system ].filesystem.num_files ; i++ )
   {
      int size = MAX( strlen( systems[ current_system ].
                                 filesystem.files[i].filename ),
                      strlen( arguments->args[ 1 ] ) );

      if ( strncmp( systems[ current_system ].filesystem.files[i].filename, 
                    arguments->args[ 1 ], size ) == 0 )
      {
         cat_file( i );
         return;
      }
   }

   add_message( "File not found." );

   return;
}

