# Zolertia RE-Mote platform

The OpenWSN BSP (Board Support Package) for the CC2538 platform is based on the
CC2538 Foundation Firmware provided by Texas Instruments (available at:
http://www.ti.com/tool/cc2538-sw). The current version of the CC2538 Foundation
Firmware is Rev. A which dates from May 6, 2013. Information regarding the
CC2538 Foundation Firmware can be found in the CC2538 Peripheral Driver Library
User's Guide (available at: http://www.ti.com/lit/pdf/swru325) which also
dates from May 6, 2013.

## RE-Mote information

More information about the RE-Mote and Zolertia products can be found at the
usual places:

* [Zolertia website](http://www.zolertia.io)
* [Zolertia Wiki page](https://github.com/Zolertia/Resources/wiki)

## Port status

This port is heavily based on the OpenMote (thanks!).  Support for the 2.4Ghz RF
interface should be working OK, pending the following features:

* CC1200 Sub-1GHz RF chip
* MicroSD
* Shutdown mode (enables powering-down the RE-Mote down to 150nA)

## A first example

To compile and upload the RE-Mote:

`openwsn-fw$ scons board=remote toolchain=armgcc bootload=/dev/ttyUSB0 oos_openwsn`

As default it uses the BSL script to flash over the USB port, it doesn't
require to manually input the bootloader sequence, as it is done automatically
by the on-board PIC.

To start the network run:

`openwsn-sw/software/openvisualizer$ sudo scons runweb`

Select a mote and toggle the RPL DAGroot state.
