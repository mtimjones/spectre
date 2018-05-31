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

int find_file( int system, char *filename )
{
   for ( int i = 0 ; i < MAX_FILES ; i++ )
   {
      if ( systems[ system ].filesystem.files[i].active )
      {
         int size = MAX( strlen( systems[ system ].
                           filesystem.files[i].filename ), strlen( filename ) );

         if ( strncmp( systems[ system ].filesystem.files[i].filename,
                       filename, size ) == 0 )
         {
            return i;
         }
      }
   }

   return -1;
}

int find_empty_file( int system )
{
   for ( int i = 0 ; i < MAX_FILES ; i++ )
   {
      if ( systems[ system ].filesystem.files[i].active == 0 )
      {
         return i;
      }
   }

   return -1;
}

int find_empty_process( void )
{
   processes_t *processes = &systems[ current_system( ) ].processes;

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
   processes_t *processes = &systems[ current_system( ) ].processes;
   filesystem_t *filesystem = &systems[ current_system( ) ].filesystem;
   char line[ MAX_MSG_SIZE ];

   if ( --filesystem->files[findex ].quantity == 0 )
   {
      filesystem->files[findex].active = 0;
   }

   // Load the process with file info.
   processes->process[ pindex ].install_ticks =
      parse_attribute( filesystem->files[ findex ].contents, "InstallTicks:" );
   processes->process[ pindex ].run_period =
      parse_attribute( filesystem->files[ findex ].contents, "RunPeriod:" );
   processes->process[ pindex ].run_ticks =
      parse_attribute( filesystem->files[ findex ].contents, "RunTicks:" );
   processes->process[ pindex ].argument = arg; 
   strcpy( processes->process[ pindex ].name, 
            filesystem->files[ findex ].filename );
   processes->process[ pindex ].pid = getRand( 10000 );
   processes->process[ pindex ].exploit = filesystem->files[ findex ].exploit;

   // Setup the process state
   processes->process[ pindex ].state = INSTALLING;
   processes->process[ pindex ].state_value = 
      processes->process[ pindex ].install_ticks;

   // Activate the process.
   processes->process[ pindex ].flags.active = 1;

   sprintf( line, "[%d] %s started.",
            processes->process[ pindex ].pid, 
            processes->process[ pindex ].name );
   add_message( line );

   return;
}

int find_system( char *address )
{
   for ( int i = 0 ; i < NUM_SYSTEMS ; i++ )
   {
      int size = MAX( strlen( address  ), strlen( systems[ i ].ip_address ) );
      if ( strncmp( address, systems[ i ].ip_address, size ) == 0 )
      {
         return i;
      }
   }

   return -1;
}
