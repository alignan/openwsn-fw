The OpenWSN BSP (Board Support Package) for the CC2538 platform is based on the
CC2538 Foundation Firmware provided by Texas Instruments (available at:
http://www.ti.com/tool/cc2538-sw). The current version of the CC2538 Foundation
Firmware is Rev. A which dates from May 6, 2013. Information regarding the
CC2538 Foundation Firmware can be found in the CC2538 Peripheral Driver Library
User's Guide (available at: http://www.ti.com/lit/pdf/swru325) which also
dates from May 6, 2013.

To compile and upload the RE-Mote:

scons board=remote toolchain=armgcc bootload=/dev/ttyUSB0 oos_openwsn

As default it uses the BSL script to flash over the USB port, it doesn't
require to manually input the bootloader sequence, as it is done automatically
by the on-board PIC.
