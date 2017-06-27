# SmartCurtain

Welcome to my smartcurtain repository. Herein lies the source for my smartcurtain project i hacked together to make an automated curtain solution at home.

## Getting started
See each seperate folder on details for how to set up the project yourself.

## Instructions

1. Electronics: I used the ESP8266 NodeMCU devboard for controlling the application, a N20 geared dc motor and some electronics to set it up. See schematics in electronics folder.
2. Firmware: After connecting the electronics, flash the firmware on the nodemcu. This is done with arduino and the community library for ESP8266.
3. Brackets: 3D print the meshes in mesh folder for the holder for the motor. You may suit this to your application.
4. System: Deploy the MQTT broker found in server folder and make sure the ESP connects to it.
5. Clients: Run the client applications found in the clients folder for operating the system

## Demo

Not yet avaliable

## LICENCE

The MIT License (MIT)

Copyright (c) 2017 Anders Hurum

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
E 
