# About
This project was inspired by [BrainwaveOSC](https://github.com/trentbrooks/BrainWaveOSC) by [trentbrooks](https://github.com/trentbrooks).
Actually this project is under intensive development. The main goal is creating a simple application powered with QT and easy to use.

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
After run application, wait a moment to detect Bluetooth devices. Then press button connect. At this moment you should see in RfcommMonitor tab hexadecimals.

# Issues
* Device is not detected
    - If device won't discovered automatically, try to press pair button.
    - If won't resolve, remove your device from devices list. In some configurations you'll need to pair Your device.
* Device is connected, but hexadecimals not appear
    - Try to press disconnect, then connect

# TODO
[ ] Implement friendly diagnostic interface to easily readable (diagnostic messages in tab or window)
[ ] Implement notifications when changing status
[ ] Implement ThinkGear Parser
[ ] Implement OSC

# Contact
To contact me, please use my [contact form](https://freeshell.de/~arturwro/contact.php?lang=en)
