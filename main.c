#include "headers.h"

unsigned int GameRunning = 1;
unsigned int GameTime = 0;

int main( int argc, char *argv[] )
{
   srand( time( NULL ) );

   init_user_input( );

   init_messages( );

   win_startup( );

   add_message( "Connected to 18.75.0.9" );
   add_message( "Type help for more information." );

   init_system( 0 );

   win_update( );

   while ( GameRunning )
   {
      unsigned long long start = getTimestamp( );

      handle_user_input( );

      system_simulate( );

      // Update the window
      win_update( );

      while ( getTimestamp( ) < start + MS_PER_FRAME );

      GameTime++;
   }

   win_shutdown( );

   return 0;
}

