# pirthing

An ESP8266 hosted PIR sensor to send on/off commands to lights managed in the [Lights](https://github.com/kenkl/lights) app. This is based vaugely on [buttonthing](https://github.com/kenkl/buttonthing) and [MotionNightlight](https://github.com/kenkl/MotionNightlight), except we don't need PWM logic to turn on/off a light; we'll just fling an on/off over to the Lights app. We will control the timings here, like MotionNightlight, to extend the on-period if additional motion is detected, for instance. 

It is an exceedingly simple circuit, but it does do something interesting:

![Fritzing view of pirthing](https://i.imgur.com/cvvKY6H.png "Fritzing view of pirthing")

(the .fzz is included in the project.)

Of note... Although the [PIR Sensor](https://www.adafruit.com/product/189) requires a 5V supply voltage, its output on the signal pin *is* 3.3V, so is safe to use with ESP8266 (and RaspberryPi, BTW) as long as there's a 5V rail to power it.

Also, the ESP8266 appears to only do an internal PULLDOWN on GPIO16, so we're limited to using that pin for this PIR (it signals as HIGH). 

