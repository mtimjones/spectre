
#define MAX_FILE_NAME       17
#define MAX_FILE_SIZE      257
#define MAX_FILE_ATTR       10
#define MAX_FILES           10
#define MAX_PROCESSES       16
#define MAX_IP_ADRS_SIZE    16
#define MAX_HOST_INFO_SIZE  50
#define MAX_TRACEABLE_HOSTS  5

typedef enum {
   INVALID,
   INSTALLING,
   RUNNING,
   SLEEPING,
   EXITING,
   ZOMBIE,
} state_t;

typedef int (*exploit_func)( int process_index, state_t state );

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
   unsigned int   install_ticks;
   unsigned int   run_period;
   unsigned int   run_ticks;
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
   unsigned int alive:1;
   unsigned int discoverable:1;
   unsigned int tracingActive:1;
   unsigned int miningActive:1;
} system_flags;

typedef struct
{
   char              ip_address[ MAX_IP_ADRS_SIZE ];
   char              hostinfo[ MAX_HOST_INFO_SIZE ];
   filesystem_t      filesystem;
   processes_t       processes;
   traceable_hosts_t traceable_hosts;
//   unsigned int  delay;
//   sim_func_t   ServerSimulationFunction;
   system_flags      flags;
} system_t;

#define NUM_SYSTEMS   4

extern system_t systems[];

#define MAX_SYS_STACK_DEPTH   100

typedef struct
{
   int entry[ MAX_SYS_STACK_DEPTH ];
   int top_index;
} system_stack_t;

// Macros

#define TRACER \
{ "tracer",                                            \
     "Trace hosts from this system.  Can be used to\n" \
     "identify other connected hosts.\n"               \
     "InstallTicks: 1000\n"                            \
     "RunPeriod: 1000\n"                               \
      "RunTicks: 2\n",                                 \
   "rwxrwxrwx",                                        \
   .exploit = tracer_func,                             \
   .quantity = 1,                                      \
   .active = 1 }

#define SLEEPER \
{ "sleeper",                                                \
     "Put a named process (pid) to sleep for 7 seconds.\n"  \
     "This can be used to passively manipulate a system.\n" \
     "Strength: 7\n"                                        \
     "InstallTicks: 2000\n"                                 \
     "RunTicks: 1\n"                                        \
     "RunPeriod: 3000\n",                                   \
   "rwxrwxrwx",                                             \
   .exploit = sleeper_func,                                 \
   .quantity = 1,                                           \
   .active = 1 }

#define MINER \
{ "miner",                                                    \
     "Mine bitcoin from a system.  You must have a\n"         \
     "collector process in your home system to collect it.\n" \
     "Strength: 5\n"                                          \
     "InstallTicks: 6000\n"                                   \
     "RunTicks: 0\n"                                          \
     "RunPeriod: 5000\n",                                     \
   "rwxrwxrwx",                                               \
   .quantity = 1,                                             \
   .active = 1 }

#define DATATAP \
{ "datatap",                                                     \
      "Tap into a running process to reveal its private data.\n" \
      "Strength: 5\n"                                            \
      "InstallTicks: 8000\n"                                     \
      "RunTicks: 0\n"                                            \
      "RunPeriod: 2000\n",                                       \
   "rwxrwxrwx",                                                  \
   .exploit = datatap_func,                                      \
   .quantity = 1,                                                \
   .active = 1 }

