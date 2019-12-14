# pirthing

COMING SOON!

An ESP8266 hosted PIR sensor to send on/off commands to lights managed in the [Lights](https://github.com/kenkl/lights) app. This is based vaugely on [MotionNightlight](https://github.com/kenkl/MotionNightlight), except we don't need PWM logic to turn on/off a light; we'll just fling an on/off over to the Lights app. We will control the timings here, like MotionNightlight, to extend the on-period if additional motion is detected, for instance. 
