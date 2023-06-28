# About
QBrainwaveOSC was inspired by [BrainwaveOSC](https://github.com/trentbrooks/BrainWaveOSC) by [trentbrooks](https://github.com/trentbrooks),
and written in QT. It converts signals from Neurosky(r) devices connected as serial port and sends them as OSC.

# Build
To build this project you'll need only QT (5 or 6) and cmake.
Type:
```
cd QBrainwaveOSC
mkdir build
cd build
cmake ..
cmake --build .
cmake --install .
```

# Usage

* Connect you device to Bluetooth (Neurosky(r) devices are connecting as Serial Port)
* Choose serial port 
* Be sure if OSC settings are correct (OSC settings can be changed during running). 
* Press connect to start.

If you can see changing graphs, device is working correctly.

# Contact
To contact me, please use my [contact form](https://freeshell.de/~arturwro/contact.php?lang=en)
