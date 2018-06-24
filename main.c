#include "headers.h"

unsigned int GameRunning = 1;
unsigned int GameTime = 0;

int main( int argc, char *argv[] )
{
   srand( time( NULL ) );

   init_user_input( );

   init_messages( );

   win_startup( );

   add_message( "CyberOS uKernel started (18.75.0.9)." );
   add_message( "CortextLink detected... attached." );
   add_message( "Process slots available... 4." );
   add_message( "" );
   add_message( "Type help for more information." );

   add_chat_message( "Chat connection opened." );
   add_chat_message( "You're back..." );
   add_chat_message( "Let's start with something simple." );
   add_chat_message( "Your task is to kill the drone" );
   add_chat_message( "passenger.  An ingress node is" );
   add_chat_message( "available through 151.98.15.3." );
   add_chat_message( "Find your way to the drone" );
   add_chat_message( "through this network..." );

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

