// Messages are the scrolling messages within the UI.
// This file contains update and retrieval functions.

#include "headers.h"

#define MAX_MSG_SIZE   ( NCOLS - 2 )

static int write_ptr = 0;
static int chat_write_ptr = 0;

char messages[ MAX_MESSAGES ][ MAX_MSG_SIZE ];
char chat_messages[ MAX_CHAT_MESSAGES ][ MAX_CHAT_MSG_SIZE ];

void init_messages( void )
{
   bzero( messages, sizeof( messages ) );
   bzero( chat_messages, sizeof( chat_messages ) );
   return;
}

void add_message( char *msg )
{
   int i = 0;
   size_t len = strlen( msg );

   // Copy the message into the buffer and pad with spaces
   while ( i < ( MAX_MSG_SIZE - 1 ) )
   {
      if ( i < len ) messages[ write_ptr ][ i ] = msg[ i ];
      else messages[ write_ptr ][ i ] = ' ';
      i++;
   }

   // Null terminate
   messages[ write_ptr ][ ( MAX_MSG_SIZE - 1 ) ] = 0;

   if ( ++write_ptr >= MAX_MESSAGES  )
   {
      write_ptr = 0;
   }

   return;
}

void add_chat_message( char *msg )
{
   int i = 0;
   size_t len = strlen( msg );

   // Copy the message into the buffer and pad with spaces
   while ( i < ( MAX_CHAT_MSG_SIZE - 1 ) )
   {
      if ( i < len ) chat_messages[ chat_write_ptr ][ i ] = msg[ i ];
      else chat_messages[ chat_write_ptr ][ i ] = ' ';
      i++;
   }

   // Null terminate
   chat_messages[ chat_write_ptr ][ ( MAX_CHAT_MSG_SIZE - 1 ) ] = 0;

   if ( ++chat_write_ptr >= MAX_CHAT_MESSAGES  )
   {
      chat_write_ptr = 0;
   }

   return;
}

char *get_message( int pos )
{
   int read_ptr;

   read_ptr = write_ptr + pos;

   if (read_ptr >= MAX_MESSAGES )
   {
      read_ptr -= MAX_MESSAGES;
   }

   return &messages[ read_ptr ][ 0 ];
}

char *get_chat_message( int pos )
{
   int read_ptr;

   read_ptr = chat_write_ptr + pos;

   if (read_ptr >= MAX_CHAT_MESSAGES )
   {
      read_ptr -= MAX_CHAT_MESSAGES;
   }

   return &chat_messages[ read_ptr ][ 0 ];
}
