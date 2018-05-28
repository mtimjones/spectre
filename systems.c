#include "headers.h"
#include <ctype.h>

system_t systems[ NUM_SYSTEMS ] = { 
   { 
      .ip_address = "127.0.0.1",
      .hostinfo = "Neural Implant - Home Edition V4.5663.4A",
      .flags = {
         .timezone = 0,
         .probeable = 1,
         .discoverable = 1,
      },
      .filesystem = { 
            .files[0] = 
               // 1234567890123456789012345678901234567890123456789012345678
               {  "README", 
                   "CyberOS README\n"
                   "Type help for command information.\n"
                   "WARNING: you are required to follow all laws under the\n"
                   "IT ACT of 2064.  Crimes against people, property, or the\n"
                   "Government are punishable by death.\n",
                  .attributes = "rw-r--r--", 
                  .quantity = 1,
                  .active = 1 },
            .files[1] = { 
                  "bitcoin", 
                   "100\n", 
                  "rw-rw-rw-", 
                  .quantity = 1,
                  .active = 1 },
            .files[2] = { 
                  "tasks", 
                   "quest information\n", 
                  "rw-r--r--", 
                  .quantity = 1,
                  .active = 1 },
            .files[3] = {
                  "tracer",
                   "Trace hosts from this system.\n"
                   "InstallTime: 300\n"
                   "RunTime: 200\n",
                  "rwxrwxrwx", 
                  .exploit = tracer_func,
                  .quantity = 1,
                  .active = 1 },
      },
      .processes = {
         .process[0] = {
            .name = "CyberOS uKernel",
            .pid = 1335,
            .strength = 15,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[1] = {
            .name = "Sentry",
            .pid = 6168,
            .strength = 20,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 1,
            },
         },
      },
   },

   { .ip_address = "10.0.0.1",
     .hostinfo = "Test host info",
     .filesystem = {},
      .flags = {
         .timezone = 300,
         .probeable = 0,
         .discoverable = 0,
      },
   },
};

int current_system = 0;


void system_command( args *arguments )
{
   for ( int i = 0 ; i < MAX_COMMANDS ; i++ )
   {
      int size = MAX( strlen( arguments->args[ 0 ] ), 
                      strlen( command_list[ i ].name ) );

      if ( strncmp( arguments->args[ 0 ], command_list[ i ].name, size ) == 0 )
      {
         ( command_list[ i ].function )( arguments );
         return;
      }
   }

   add_message( "Unknown command." );

   return;
}


void system_exec( char* line )
{
   args arguments = {0, (char*)0, (char*)0, (char*)0};

   parse_args( line, &arguments );

   system_command( &arguments );

   return;
}


void system_simulate( void )
{
   processes_t *processes = &systems[ current_system ].processes;
   int ret;

   for ( int i = 0 ; i < MAX_PROCESSES ; i++ )
   {
      if ( processes->process[ i ].flags.active == 1 )
      {
         // If state value is non-zero, process the state
         if ( processes->process[ i ].state_value )
         {
            switch( processes->process[ i ].state )
            {
               case INSTALLING:
                  processes->process[ i ].state_value -= 1;
                  if ( processes->process[ i ].state_value <= 0 )
                  {
                     processes->process[ i ].state = RUNNING;
                     processes->process[ i ].state_value =
                        processes->process[ i ].run_time;
                  }
                  break;

               case RUNNING:
                  processes->process[ i ].state_value -= 1;
                  if ( processes->process[ i ].state_value <= 0 )
                  {
                     processes->process[ i ].state_value = 
                        processes->process[ i ].run_time;
                     if ( processes->process[ i ].exploit )
                     {
                        ret = (processes->process[ i ].exploit)
                                 ( current_system );

                        if ( ret == 1 )
                        {
                           processes->process[ i ].flags.active = 0;
                        }
                     }
                  }
                  break;

               case SLEEPING:
                  processes->process[ i ].state_value -= 1;
                  if ( processes->process[ i ].state_value <= 0 )
                  {
                     processes->process[ i ].state = RUNNING;
                     processes->process[ i ].state_value =
                        processes->process[ i ].run_time;
                  }
                  break;

               case INVALID:
               case ZOMBIE:
               default:
                  break;
            }
         }
      }
   }

   return;
}

