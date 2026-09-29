## Dev info
Author: Conner O'Reilly
Wisc email: ccoreilly@wisc.edu
Last modified date: 09/29/2026
Other contact info(optional): oreillyconner@protonmail.com

## BMS TELEM FIRMWARE
This is the folder that stores all of the BMS telem data firmware. This is the most complicated firmware of all three systems. 
To be complete this firmware must do the following:
1. On boot: Set up the clock, watchdog, CAN, I2C, and NOR flash. Find where the last valid log entry was so logging picks up where it left off.
2. Check the state: Decide whether the pack is idle (not powering the AUV), active, in a handover, in service mode, or faulted. Base this on current draw, FET state from  the BMS, and whether the AUV is talking on CAN.
3. Check the data: Look for readings that are stale, out of range, changing too fast, or showing cell imbalance or high temperature. Update the fault flags.
4. Read from the BMS over I2C at the polling rate for the current state (fast when active, slow when idle). If the read fails or the data hasn't updated, count it as an error.
5. Log to NOR flash at the logging rate for the current state. Buffer entries in RAM and write them in full pages, so a slow flash operation never holds up the rest of the loop.
6. Send to other modules: Send a regular heartbeat with status, and send an extra message right away whenever a fault or the state changes.
7. Handle incoming messages: Check that each command is one you accept and is allowed in the current state, run it, and reply with success or failure. Split long jobs like log downloads into pieces handled a little each loop.
8. Update the display if the pack isn't idle.
9. Feed the watchdog only if every step above completed this loop.
10. Go to low power if idle and nothing is pending. Turn off the display, put the flash to sleep, put the CAN transceiver in standby, and stop the MCU. Wake up on a timer for the slow poll, on CAN activity, on a BMS alert, or on the magnet.

## Structure
                          WAUV interperter
                                 |
                          ---------------
                        |               |
                   Telem Module.   Telem Module
                        |               |
                     BMS/AFE         BMS/AFE  

The AFE_Control_Program folder is where the BMS/AFE firmware will be stored. 
The AUV_Control_Program folder is where the WAUV interperter goes.
The TELEM_Control_Program folder is where the TELEM modules firmware will go.


## TODO 
Write all firmware for all three systems.

## Describe all future files here.

## External Documentation
https://docs.ros.org/en/rolling/index.html
https://ardupilot.org/sub/
