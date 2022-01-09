fehler das die erste led grün wird:
beheben mit der installation von: (ESP8266 by ESP8266 Community) funktioniert es und zwar 2.7.4

pagebuilder 1.4.2

datenbus on led an d3

rtc an d1 - SCL 
und d2 -> SDA

* [AutoConnect](https://github.com/Hieromon/AutoConnect)

arduino pyserial big sur fix: from: https://forum.arduino.cc/t/pyserial-and-esptools-directory-error/671804/5
I updated my mac to macOS 11.0.1 Big Sur today and found the same problem.
Instead of commenting the lines that flszen mentioned I fixed the source of the problem.

Context

Arduino IDE version: 1.8.13
esp8266 Core version: 2.7.4
My workaround is as follows:

1.- Open ~/Library/Arduino15/packages/esp8266/hardware/esp8266/2.7.4/tools/pyserial/serial/tools/list_ports_osx.py
2.- Comment out lines 29 and 30 and append these lines:
iokit = ctypes.cdll.LoadLibrary('/System/Library/Frameworks/IOKit.framework/IOKit')
cf = ctypes.cdll.LoadLibrary('/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation')

The code should look like this:

#iokit = ctypes.cdll.LoadLibrary(ctypes.util.find_library('IOKit'))
#cf = ctypes.cdll.LoadLibrary(ctypes.util.find_library('CoreFoundation'))
iokit = ctypes.cdll.LoadLibrary('/System/Library/Frameworks/IOKit.framework/IOKit')
cf = ctypes.cdll.LoadLibrary('/System/Library/Frameworks/CoreFoundation.framework/CoreFoundation')
This is the same fix that the developers of pyserial made (Latest version of the file here 14) to fix this issue but the esp8266 core uses a 2 year old version of pyserial, so until they update the library this will still be an issue.