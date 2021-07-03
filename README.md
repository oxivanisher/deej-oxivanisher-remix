# deej-oxivanisher-remix
My remix for the deej project. I use 6 knobs for audio control with a Arduino Pro Micro in VSCode with PlatformIO.

## Origins
* The main project from [omriharel](https://github.com/omriharel) is located [here on github](https://github.com/omriharel/deej/).
* The RGB led source code addition from [ocyrus99](https://www.thingiverse.com/ocyrus99) was found on [thingiverse](https://www.thingiverse.com/thing:4599505).

## Wiring
| Pin    | What is connected               |
|--------|---------------------------------|
| 5      | PWM output for the ws2812b LEDs |
| A0     | Knob 1                          |
| A1     | Knob 2                          |
| A2     | Knob 3                          |
| A3     | Knob 4                          |
| A6 (4) | Knob 5                          |
| A7 (6) | Knob 6                          |
| VCC    | 5V rail for the knobs           |
| GND    | Ground rail for the knobs       |
