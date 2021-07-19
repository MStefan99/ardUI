# Arduino emulator

Previously, ardUI was developed in a PlatformIO environment but this approach proved to be difficult to maintain since
it required an Arduino board to run the code and debugging was near impossible. Now ardUI has been migrated to gcc and
can be run or debugged on any computer which simplifies the development process a lot. But in order to emulate some
useful Arduino functions and, most importantly, its program flow with setup() and loop() functions, which ardUI heavily
relies upon, this emulator was developed. It is pretty simple and should never be used in a real system but it ensures
that ardUI stays compatible with Arduino out-of-the-box.  
