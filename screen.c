#include "headers.h"
#include <ncurses.h>

WINDOW *mainwin;

// Offset to center game pane in the available window.
int offsetx, offsety;

int get_user_char( void )
{
   int c;

   c = wgetch( mainwin );

   if ( c != ERR )
   {
      return c;
   }

   return 0;
}

void win_startup( void )
{
   initscr( );
   cbreak( );
   noecho( );
   curs_set( 0 );
   nonl( );

   offsety = ( LINES - NLINES ) / 2;
   offsetx = ( COLS - NCOLS ) / 2;

   mainwin = newwin( NLINES, NCOLS, offsety, offsetx );
   nodelay( mainwin, TRUE );
   keypad( mainwin, TRUE );

   return;
}


void win_update( void )
{
   int Y, X;

   extern int exit_y, exit_x;

   wborder( mainwin, 0, 0, 0, 0, 0, 0, 0, 0 );

   for ( int i = 0 ; i < MAX_MESSAGES ; i++ )
   {
      mvwprintw( mainwin, ( i+1 ), 1, "%s", get_message( i ) );
   }

   mvwprintw( mainwin, NLINES-2, 1, 
              "                                                          " );
   mvwprintw( mainwin, NLINES-2, 1, "%s", get_user_input_line() );

   wrefresh( mainwin );

   return;
}


void win_shutdown( void )
{
   delwin( mainwin );

   endwin( );

   return;
}

