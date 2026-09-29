## Dev info
Author: Conner O'Reilly
Wisc email: ccoreilly@wisc.edu
Last modified date: 09/29/2026
Other contact info(optional): oreillyconner@protonmail.com

## WAUV BMS FIRMWARE
This repository is where all of the firmware for the custom battery managment system will be. This firmware has seperate folders for each node. Since
everything is running on stms we dont have the headroom to easily install all programs onto each machine. 

The system is a three tiered distributed system to ensure full comunnication and low latencey where it matters. The WAUV interperter will convert between
our custom network and send ROS2 commands to the AUV.(We also might use ardu sub then to the pixhawk. Might be easier) The telem module will handle all 
communication to the battery as well as being the device to program the BMS/AFE chip. It also needs to interact to external computers for sending telemetry data.
The BMS/AFE firmware will strictly handle managing the battery and send neccessary updates to the telem module. When in operation the polling rate will significantly incresase compared to sleep.

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