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

   {
      char line[80]={0};
      sprintf( line, "%s == %d", line, value );
      add_message( line );
   }

   return value;
}

