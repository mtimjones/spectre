#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <strings.h>
#include <string.h>

#include "systems.h"
#include "commands.h"
#include "exploits.h"

// Size of the UI
#define NLINES      ( 32 )
#define NCOLS       ( 60 )
#define CCOLS       ( 40 )

// 100Hz Game Loop
#define MS_PER_FRAME  10

// Max number of window messages
#define MAX_MESSAGES       ( NLINES - 3 )
#define MAX_MSG_SIZE       ( NCOLS - 2  )
#define MAX_CHAT_MESSAGES  ( NLINES - 2 )
#define MAX_CHAT_MSG_SIZE  ( CCOLS - 2  )

// Messages API
void init_messages( void );
void add_message( char *msg );
char* get_message( int pos );
void add_chat_message( char *msg );
char *get_chat_message( int pos );

// Screen API
void win_startup( void );
void win_update( void );
void win_shutdown( void );
int  get_user_char( void );

// Time API
unsigned long long getTimestamp( void );
extern unsigned int GameTime;

// User Input API
void init_user_input( void );
void handle_user_input( void );
char *get_user_input_line( void );

// Systems API
void system_simulate( void );
void system_exec( char *line );

// Helpers API
void parse_args( char *line, args *arguments );
int  parse_attribute( char *line, char *attribute );
int  find_file( int system, char *filename );
int  find_empty_file( int system );
int  find_empty_process( void );
int  find_process( unsigned short pid );
void create_process_from_file( int pindex, int findex, unsigned int arg );
int  find_system( char *ip_address );
void move_file( int to, int from, char *file );
int  can_execute( void );

// System stack API
void init_system( int system );
int  current_system( void );
int  system_stack_empty( void );
void set_current_system( int system );
void push_system( int system );
int  pop_system( void );

// RNG Functions 
#define getSRand()      ( ( float ) rand( ) / ( float ) RAND_MAX )
#define getRand( x )    ( int ) ( ( x ) * getSRand( ) )


