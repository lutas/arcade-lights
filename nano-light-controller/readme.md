# About
This is a device to turn on/off multiple button LEDs. The intention is for a host to communicate over serial to control which buttons are enabled when playing games on an arcade cabinet.

The code is intended for an Arduino Nano which has been setup to control 8 digital button LEDs through digital pins 2, 4, 6, 8, 10, 12, 14 (A0) and 16 (A2).

# Commands
Serial commands are sent as a series of bytes:

Firstly, to specify the command type to interpret the data
    {command-marker}{command}
e.g.      0xFF         0x01

and then followed by a stream of data.

Once the command has set, the data can continue to be streamed until the next command.

## Supported commands
The controller supports the following commands:

### Off
Disable any data reading until the next command. 

Command: **0x0**
Data: n/a

### Set light state
Typical use case, send data to set the active state of a light.

Command: **0x01**
Data: {lightIndex (5 bits): state (3 bits)} (1 byte)
e.g. to set light 3 to FastPulse  0x00011001 

*Supported states*
|Binary|State|
|------|-----|
| 000  | Off |
| 001  | On  |
| 010  | ShortPulse |
| 011  | LongPulse |

### Set pulse times
Modify the on and off delay in milliseconds for the supported pulses:

Command: **0x02**
Data: {pulseId} (1 byte) {timeInMillis} (4 bytes)
