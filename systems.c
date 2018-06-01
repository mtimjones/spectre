#include "headers.h"
#include <ctype.h>

system_t systems[ NUM_SYSTEMS ] = { 
   { 
      .ip_address = "18.75.0.9",
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
                "0\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
         .files[2] = { 
               "task", 
               "Your task is to kill the drone passenger through whatever\n"
               "means possible.  An ingress node is available to you\n"
               "through 151.98.15.3.\n",
               "rw-r--r--", 
               .quantity = 1,
               .active = 1 },
         .files[3] = {
               "tracer",
                "Trace hosts from this system.\n"
                "InstallTicks: 1500\n"
                "RunPeriod: 2000\n"
                "RunTicks: 2\n",
               "rwxrwxrwx", 
               .exploit = tracer_func,
               .quantity = 1,
               .active = 1 },
         .files[4] = {
               "sleeper",
                "Put a named process (pid) to sleep for 7 seconds.\n"
                "This can be used to passively manipulate a system.\n"
                "InstallTicks: 3000\n"
                "RunTicks: 1\n"
                "RunPeriod: 6000\n",
               "rwxrwxrwx", 
               .exploit = sleeper_func,
               .quantity = 2,
               .active = 1 },
      },
      .processes = {
         .process[0] = {
            .name = "CyberOS uKernel",
            .pid = 1335,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[1] = {
            .name = "CortexLink",
            .pid = 6168,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
      },
      .traceable_hosts = {
      },
   },

   {
      .ip_address = "151.98.15.3",
      .hostinfo = "Honkaku Hanko Vending",
      .flags = {
         .timezone = 300,
         .probeable = 1,
         .discoverable = 1,
      },
      .filesystem = {
         .files[0] = { 
               "bitcoin", 
                "50\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
         .files[1] = { 
               "manifest", 
                "** binary data\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
         .files[2] = { 
               "orders", 
                "** binary data\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
      },
      .processes = {
         .process[0] = {
            .name = "UserInput",
            .pid = 9175,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[1] = {
            .name = "HankoLink",
            .pid = 4292,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[2] = {
            .name = "HankoDiag",
            .pid = 3811,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 1,
            },
         },
      },
      .traceable_hosts = {
         "151.98.15.9"
      },
   },

   {
      .ip_address = "151.98.15.9",
      .hostinfo = "Metropolitan Router",
      .flags = {
         .timezone = 300,
         .probeable = 1,
         .discoverable = 1,
      },
      .filesystem = {
         .files[0] = { 
               "routetable", 
                "** binary data\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
         .files[1] = { 
               "dronelist", 
                "Drone 121.75.9.192 active in area.\n",
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
      },
      .processes = {
         .process[0] = {
            .name = "router",
            .pid = 9175,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[1] = {
            .name = "sentry",
            .pid = 9189,
            .install_ticks = 0,
            .run_period = 2000,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 1,
            },
         },
      },
      .traceable_hosts = {
      },
   },

   {
      .ip_address = "121.75.9.192",
      .hostinfo = "Nissan Telematics System, V2.3108.AX",
      .flags = {
         .timezone = 300,
         .probeable = 1,
         .discoverable = 1,
      },
      .filesystem = {
         .files[0] = { 
               "bitcoin", 
                "100\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
         .files[1] = { 
               "mapinfo", 
                "World street map\n"
                "** binary data\n", 
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
         .files[2] = { 
               "geolocation", 
                "Awaiting geo location update.\n",
               "rw-rw-rw-", 
               .quantity = 1,
               .active = 1 },
      },
      .processes = {
         .process[0] = {
            .name = "Telematics Server",
            .pid = 3395,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[1] = {
            .name = "AirNet Link",
            .pid = 9375,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[2] = {
            .name = "Auto Pilot",
            .pid = 536,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 1,
            },
         },
         .process[3] = {
            .name = "Diags System",
            .pid = 9315,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 0,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 0,
            },
         },
         .process[4] = {
            .name = "sentry",
            .pid = 1847,
            .install_ticks = 0,
            .run_period = 0,
            .run_ticks = 2000,
            .argument = 0,
            .state = RUNNING,
            .flags = {
               .active = 1,
               .killable = 1,
            },
         },
      },
      .traceable_hosts = {},
   },
};


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

   if ( arguments.num_args > 0 )
   {
      system_command( &arguments );
   }

   return;
}


void system_simulate( void )
{
   processes_t *processes = &systems[ current_system( ) ].processes;
   char line[ MAX_MSG_SIZE ];
   int ret;

   // Only allow this to execute every 500ms.
   // Each state gets called for active processes, every 500ms

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
                  processes->process[ i ].state_value -= MS_PER_FRAME;

                  if ( processes->process[ i ].state_value <= 0 )
                  {
                     processes->process[ i ].state = RUNNING;
                     processes->process[ i ].state_value =
                        processes->process[ i ].run_period;

                     if ( processes->process[ i ].exploit )
                     {
                        ret = (processes->process[ i ].exploit)( i , INSTALLING );
                     }
                  }
                  break;

               case RUNNING:
                  processes->process[ i ].state_value -= MS_PER_FRAME;
                  if ( processes->process[ i ].state_value <= 0 )
                  {
                     processes->process[ i ].state_value = 
                        processes->process[ i ].run_period;

                     if ( processes->process[ i ].exploit )
                     {
                        if ( processes->process[ i ].run_ticks )
                        {

                           ret = (processes->process[ i ].exploit)( i, RUNNING );
                           if ( --processes->process[ i ].run_ticks == 0 )
                           {
                              ret = (processes->process[ i ].exploit)( i, EXITING );
                           }

                           if ( ret == 1 )
                           {
                              sprintf( line, "[%d]+ Done   %-17s",
                                       processes->process[ i ].pid,
                                       processes->process[ i ].name );
                              add_message( line );
                              processes->process[ i ].flags.active = 0;
                           }

                        }
                     }
                  }
                  break;

               case SLEEPING:
                  processes->process[ i ].state_value -= MS_PER_FRAME;
                  if ( processes->process[ i ].state_value <= 0 )
                  {
                     processes->process[ i ].state = RUNNING;
                     processes->process[ i ].state_value =
                        processes->process[ i ].run_period;
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

