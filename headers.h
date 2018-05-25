#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <strings.h>
#include <string.h>

// Size of the UI
#define NLINES      ( 32 )
#define NCOLS       ( 60 )

// 50Hz Game Loop (50FPS)
#define MS_PER_FRAME  20

// Max number of window messages
#define MAX_MESSAGES   ( NLINES - 3 )


// Messages API
void init_messages( void );
void add_message( char *msg );
char* get_message( int pos );

// Screen API
void win_startup( void );
void win_update( void );
void win_shutdown( void );
int  get_user_char( void );

// Time API
unsigned long long getTimestamp( void );

// User Input API
void handle_user_input( void );
char *get_user_input_line( void );

