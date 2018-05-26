
#define MAX_COMMAND_SIZE   12
#define MAX_HELP_SIZE      50

#define MAX( a, b ) ( ( (a) > (b) ) ? (a) : (b) )

#define MAX_ARGS    3

typedef struct
{
   int  num_args;
   char *args[ MAX_ARGS ];
} args;

typedef void (*command)( args *arguments );

typedef struct
{
   char    name[ MAX_COMMAND_SIZE ];
   char    help[ MAX_HELP_SIZE ];
   command function;
} commands;

#define MAX_COMMANDS  3

extern commands command_list[ MAX_COMMANDS ];

