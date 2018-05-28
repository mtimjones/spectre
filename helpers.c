#include "headers.h"
#include <ctype.h>

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


int parse_attribute( char *line, char *attribute )
{
   int value = 0;
   char *substring;

   substring = strstr( line, attribute );

   if ( substring )
   {
      while ( *substring != ' ' && *substring != 0 ) substring++;

      if ( substring )
      {
         value = atoi( substring );
      }
   }

   return value;
}

int find_file( char *filename )
{
   for ( int i = 0 ; i < MAX_FILES ; i++ )
   {
      if ( systems[ current_system ].filesystem.files[i].active )
      {
         int size = MAX( strlen( systems[ current_system ].
                           filesystem.files[i].filename ), strlen( filename ) );

         if ( strncmp( systems[ current_system ].filesystem.files[i].filename,
                       filename, size ) == 0 )
         {
            return i;
         }
      }
   }

   return -1;
}

int find_empty_process( void )
{
   processes_t *processes = &systems[ current_system ].processes;

   for ( int i = 0 ; i < MAX_PROCESSES ; i++ )
   {
      if ( processes->process[ i ].flags.active == 0 )
      {
         return i;
      }
   }

   return -1;
}


void create_process_from_file( int pindex, int findex, unsigned int arg )
{
   processes_t *processes = &systems[ current_system ].processes;
   filesystem_t *filesystem = &systems[ current_system ].filesystem;

   if ( --filesystem->files[findex ].quantity == 0 )
   {
      filesystem->files[findex].active = 0;
   }

   // Load the process with file info.
   processes->process[ pindex ].install_time =
      parse_attribute( filesystem->files[ findex ].contents, "InstallTime:" );
   processes->process[ pindex ].run_time =
      parse_attribute( filesystem->files[ findex ].contents, "RunTime:" );
   processes->process[ pindex ].argument = arg; 
   strcpy( processes->process[ pindex ].name, 
            filesystem->files[ findex ].filename );
   processes->process[ pindex ].pid = getRand( 10000 );
   processes->process[ pindex ].exploit = filesystem->files[ findex ].exploit;

   // Setup the process state
   processes->process[ pindex ].state = INSTALLING;
   processes->process[ pindex ].state_value = 
      processes->process[ pindex ].install_time;

   // Activate the process.
   processes->process[ pindex ].flags.active = 1;

   return;
}

