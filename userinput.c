#include "headers.h"
#include <ncurses.h>
#include <ctype.h>

#define MAX_LINE (NCOLS-1)

static char user_line[ MAX_LINE ];
static int cur_char;

void init_user_input( void )
{
   cur_char = 0;
   user_line[ cur_char++ ] = '$';
   user_line[ cur_char++ ] = ' ';
   user_line[ cur_char ] = 0;
}

void handle_user_input( void )
{
   int c = get_user_char( );

   if ( c == 0 )
   {
   }
   else if ( c == 0x0d )
   {
      add_message( user_line );
      system_exec( &user_line[ 2 ] );
      init_user_input( );
   }
   else if ( isprint( c ) )
   {
      if ( cur_char < MAX_LINE )
      {
         user_line[ cur_char++ ] = ( char )c;
         user_line[ cur_char ] = 0;
      }
   }
   else if ( c == KEY_BACKSPACE )
   {
      if ( cur_char > 2 )
      {
         user_line[ --cur_char ] = 0;
      }
   }

}

char *get_user_input_line( void )
{
   return user_line;
}

