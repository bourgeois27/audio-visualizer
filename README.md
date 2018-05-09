# Audio Visualizer

_Allows to view audio waves in the air_.

The Arduino UNO R3 listen to an audio signal and light up the columns of a LED panel depending on how loud the music is.
All this is possible by controlling an array of 32 smart LEDs.

## The smart LEDs
This project uses a special kind of LEDs. These LEDs have very tiny chips inside of them that allow them to communicate with each other. Rather than plug each LED into the UNO R3 separately, this tiny chip allows me to control two 4x4 LED panels with only one pin.

Since I have two panels next to each other, I have a 8 columns and 4 rows to work with. I use the output of the microphone to light up these LEDs, with more LEDs representing a louder volume.

## Interrupts

This project utilizes a feature known as interrupts. Interrupts allow to set a pin on the UNO R3 so that as sonne as the pin is activated, the current program is paused and a separate function is run. So as soon as the microphone is triggerd, the main loop will pause dans a function called `turnOn()` will run to make the LEDs light up. As soon as this function finishes, the main loop starts where it left off.

```C
attachInterrupt(digitalPinToInterrupt(MICPIN), turnOn, RISING);
```

**RISING** means that the interrupt will trigger when the pin goes from `LOW` to `HIGH`.

**FALLING** would trigger the interrupt when the pin goes from `HIGH` to `LOW`

## External Libraries

I'll be using [Adafruit's NeoPixel library][1] to interface with the LEDs.

[1]: https://github.com/adafruit/Adafruit_NeoPixel
