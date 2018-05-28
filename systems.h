
#define MAX_FILE_NAME       17
#define MAX_FILE_SIZE      257
#define MAX_FILE_ATTR       10
#define MAX_FILES           10
#define MAX_PROCESSES       16
#define MAX_IP_ADRS_SIZE    16
#define MAX_HOST_INFO_SIZE  50
#define MAX_TRACEABLE_HOSTS  5

typedef int (*exploit_func)( int system );

typedef struct
{
   char           filename[ MAX_FILE_NAME ];
   char           contents[ MAX_FILE_SIZE ];
   char           attributes[ MAX_FILE_ATTR ];
   int            quantity;
   unsigned int   active;
   exploit_func   exploit;
} file_t;

typedef struct
{
   file_t files[ MAX_FILES ];
} filesystem_t;

typedef enum {
   INVALID,
   INSTALLING,
   RUNNING,
   SLEEPING,
   ZOMBIE,
} state_t;

typedef struct
{
   unsigned int active:1;
   unsigned int killable:1;
} process_flags;

typedef struct
{
//   file_t*        file;
   char           name[ MAX_FILE_NAME ];
   unsigned short pid;
   unsigned int   install_time;
   unsigned int   run_time;
   unsigned int   strength;
   unsigned int   argument;
   state_t        state;
   int            state_value;
   process_flags  flags;
   exploit_func   exploit;
} process_t;

typedef struct
{
   process_t process[ MAX_PROCESSES ];
} processes_t;

typedef struct
{
   char ip_address[MAX_TRACEABLE_HOSTS][ MAX_IP_ADRS_SIZE ];
} traceable_hosts_t;

typedef struct
{
   unsigned int timezone:16;
   unsigned int active:1;
   unsigned int probeable:1;
   unsigned int discoverable:1;
   unsigned int tracingActive:1;
   unsigned int miningActive:1;
} system_flags;

typedef struct
{
   char         ip_address[ MAX_IP_ADRS_SIZE ];
   char         hostinfo[ MAX_HOST_INFO_SIZE ];
   filesystem_t filesystem;
   processes_t  processes;
//   unsigned int delay;
//   sim_func_t   ServerSimulationFunction;
   system_flags flags;
} system_t;

#define NUM_SYSTEMS   2

extern system_t systems[];
