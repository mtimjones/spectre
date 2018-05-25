#include "headers.h"
#include <ncurses.h>
#include <ctype.h>

#define MAX_LINE (NCOLS-1)

static char user_line[ MAX_LINE ] = { 0 };
static int cur_char = 0;

void handle_user_input( void )
{
   int c = get_user_char( );

   if ( isprint( c ) )
   {
      user_line[ cur_char++ ] = ( char )c;
   }
   else if ( c == KEY_BACKSPACE )
   {
      if ( cur_char > 0 )
      {
         user_line[ --cur_char ] = 0;
      }
   }
   else if ( c == KEY_ENTER )
   {
      add_message( user_line );
      cur_char = 0;
      user_line[ 0 ] = 0;
   }

}

char *get_user_input_line( void )
{
   return user_line;
}
