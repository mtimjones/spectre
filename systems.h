
#define MAX_FILE_NAME       17
#define MAX_FILE_SIZE      257
#define MAX_FILE_ATTR       10
#define MAX_FILES            3
#define MAX_PROCESSES       16
#define MAX_IP_ADRS_SIZE    16
#define MAX_HOST_INFO_SIZE  50

typedef struct
{
   char           filename[ MAX_FILE_NAME ];
   char           contents[ MAX_FILE_SIZE ];
   char           attributes[ MAX_FILE_ATTR ];
   unsigned int   install_time;
   int            quantity;

} file_t;

typedef struct
{
   int num_files;
   file_t files[ MAX_FILES ];

} filesystem_t;

typedef enum {
   INVALID,
   RUNNING,
   SLEEPING,
   ZOMBIE,
} state_t;

typedef struct
{
   unsigned int Active:1;
   unsigned int Killable:1;
   
} process_flags;

typedef struct
{
//   file_t*        file;
   char           name[ MAX_FILE_NAME ];
   unsigned short pid;
   unsigned int   strength;
   unsigned int   argument;
   state_t        state;
   process_flags  flags;

} process_t;

typedef struct
{
   int num_processes;
   process_t process[ MAX_PROCESSES ];

} processes_t;

typedef struct
{
   unsigned int Timezone:16;
   unsigned int Probeable:1;
   unsigned int Discoverable:1;
   unsigned int TracingActive:1;
   unsigned int MiningActive:1;

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
