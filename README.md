# Hacking simulation

An experiment in building a cyberpunk hacking simulation in C using ncurses.


               ┌──────────────────────────────────────────────────────────┐
               │                                                          │
               │                                                          │
               │                                                          │
               │Connected to 18.75.0.9                                    │
               │Type help for more information.                           │
               │$ connect 121.75.9.192                                    │
               │Connected to 121.75.9.192                                 │
               │$ ps                                                      │
               │PID  NAME              STATE                              │
               │3395 Telematics Server RUNNING                            │
               │9375 AirNet Link       RUNNING                            │
               │ 536 AutoPilot         RUNNING                            │
               │9315 GeoLocator        RUNNING                            │
               │1847 sentry            RUNNING                            │
               │$ ls                                                      │
               │rw-rw-rw-     4 bitcoin           (1)                     │
               │rw-rw-rw-    32 mapinfo           (1)                     │
               │rw-rw-rw-    33 geolocation       (1)                     │
               │$ get bitcoin                                             │
               │Security exception.                                       │
               │$ put sleeper                                             │
               │File move successful.                                     │
               │$ exec sleeper 1847                                       │
               │[9432] sleeper started.                                   │
               │[9432]+ Done   sleeper                                    │
               │$ kill 1847                                               │
               │[1847]+ Killed  sentry                                    │
               │$ get bitcoin                                             │
               │File move successful.                                     │
               │$                                                         │
               └──────────────────────────────────────────────────────────┘

