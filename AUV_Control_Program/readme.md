## Dev info
Author: Conner O'Reilly
Wisc email: ccoreilly@wisc.edu
Last modified date: 09/29/2026
Other contact info(optional): oreillyconner@protonmail.com

## AUV CONTROL FIRMWARE
The AUV Control firmware will act as a translator between the BMS network and the auv. This will take the can communication and convert it to ROS2 or arudsub(mavlink) so that it can be read by the pixhawk.
1. On boot: Set up the clock, watchdog, CAN, and the link to the Pixhawk or companion computer. Listen for heartbeats to find which packs are connected.
2. Read CAN: Take in heartbeats, status updates, fault events, and swap requests from each pack.
3. Track each pack: Keep the latest status for every pack. If a pack's heartbeat stops, mark it as missing.
4. Send pack data to the AUV: Convert each pack's voltage, current, state of charge, and temperature into a MAVLink battery status message or a ROS2 battery state topic, one per pack. Send faults and missing packs as warnings the AUV can act on.
5. Handle swap requests: When a pack asks for a swap, pass the request to the AUV. Once the AUV confirms it has stopped and is drawing low current, send the confirmation to the packs.
6. Handle commands from the AUV: Check that each command is valid, convert it to a CAN message, and send it to the right pack. Wait for an acknowledgment, retry if none comes, and report failure to the AUV if retries run out.
7. Send heartbeats both ways: Let the packs know the AUV link is alive and let the AUV know the CAN link is alive. If either side goes quiet, tell the other.
8. Feed the watchdog only if every step above completed this loop.

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

