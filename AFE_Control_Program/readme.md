## Dev info
Author: Conner O'Reilly
Wisc email: ccoreilly@wisc.edu
Last modified date: 09/29/2026
Other contact info(optional): oreillyconner@protonmail.com

## BMS/AFE FIRMWARE
     This folder stores all of the BMS/AFE control firmware. The bms system has to both dynamically manage the battery through the AFE and communicate over I2C to the Telem module.
1. On boot: Set up the clock, watchdog, and I2C target address. Configure the AFE with its protection limits (cell overvoltage and undervoltage, overcurrent, short circuit, and temperature). Load the saved state of charge and capacity.
2. Read the AFE: Get cell voltages, pack current, temperatures, and FET and protection status.
3. Check protection: Compare readings against limits. If anything is out of bounds, open the FETs and set a fault flag. The AFE's own hardware protection is the first line of defense, and this check is the second.
4. Update state of charge: Track charge in and out using the current reading, and correct the estimate from cell voltage when the pack has been resting.
6. Control the FETs: Follow handover commands from the Telem module by ramping this pack's FETs on or off. Refuse commands that would be unsafe, such as turning on with an active fault.
7. Update the data for Telem: Place the latest readings, state of charge, fault flags, and FET state where the Telem module can read them over I2C. Include a counter that increases with every update, plus a checksum, so Telem can tell whether the data is fresh and intact. Pull the alert line to Telem if a fault occurs.
8. Handle commands from Telem: Check that each command is valid and allowed in the current state, run it, and report the result for Telem to read back.
9. Feed the watchdog only if every step above completed this loop.
10. Go to low power when the pack is not powering the AUV and nothing is pending. Put the AFE in its low-power mode, measure less often, and stop the MCU. Wake up on a timer, an AFE alert, or I2C activity from Telem.

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
