# SpinToolBox
This soft was developed during my PhD (2010-2013) for automatize the measurement process in the characterization of the magnetic tunnel junction vortex oscillator.

Because it has been developed during 3 years, many parts have been modified to add features and / or add flexibility. Certain concepts that have been implemented systematically at the beginning were eventually abandoned because they are too heavy or they are needed too much work. This is the case for example of the errors handling that stopped the program for almost every mistake (for example: communication measurement tools error or syntax errors in scripts) with a notion of importance of the errors. At the end, the errors are just displayed on the consol.

## Program structure

This soft was concived in term of plugins, each managing a measuring tool. This allows people to enable or disable the tools according to their needs.

So there is a project for the main program, one by plug-in and finally two SDKs.
SDK (for standard developer kit) consists of pieces of code used in all plug-in, there are two, because I kept the possibility of introducing plug-in that do not control measurement tools, but adds functions (or script, for example). This function is not yet developed.

SDK "classic" is necessary for all plug-in, it manages:
* Error handling
* Data management and their files
* The ability to display graphs
* components for GUI


SDK "device" is required for all commander plug-in a measurement tool, it supports:
* Interface with GPIB
* Interface with VISA
* Specific error handling for  devices

## External dependency

This project depent on qt5 (https://www.qt.io/download) and the driver for GPIB and VISA for some plugings.


