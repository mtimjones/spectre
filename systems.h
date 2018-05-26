
#define MAX_FILE_NAME       17
#define MAX_FILE_SIZE      257
#define MAX_FILE_ATTR       10
#define MAX_FILES            3
#define MAX_PROCESSES       16
#define MAX_IP_ADRS_SIZE    16
#define MAX_HOST_INFO_SIZE  50

typedef struct
{
   char filename[ MAX_FILE_NAME ];
   char contents[ MAX_FILE_SIZE ];
   char attributes[ MAX_FILE_ATTR ];
   int  quantity;

} file_t;

typedef struct
{
   int num_files;
   file_t files[ MAX_FILES ];

} filesystem_t;

typedef unsigned short pid_t;

typedef struct
{
   file_t*      file;
   pid_t        pid;
   unsigned int strength;
   unsigned int install_time;
   unsigned int argument;
   unsigned int state;

} process_t;

typedef struct
{
   int num_processes;
   process_t process[ MAX_PROCESSES ];

} processes_t;

typedef struct
{
   char         ip_address[ MAX_IP_ADRS_SIZE ];
   char         hostinfo[ MAX_HOST_INFO_SIZE ];
   filesystem_t filesystem;
//   processes_t  processes;
//   unsigned int delay;
//   sim_func_t   ServerSimulationFunction;

} system_t;

