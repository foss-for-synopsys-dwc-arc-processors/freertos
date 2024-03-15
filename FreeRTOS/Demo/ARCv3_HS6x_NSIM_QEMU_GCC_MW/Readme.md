FreeRTOS Demo for ARCv3 HS6x machine emulated on QEMU/nSIM
====================

Overview
====================
 This example demonstrates basic FreeRTOS task usage, using queue and semaphore to communicate.
  * Note 1: this DEMO only supports TIMER0 and doesn't support dynamic memory management.
  * Note 2: If Metaware libraries were rebuilt for HS6x, then in Makefile define MW_HS6X_LIB.

      For example:
      buildlib -buildlib_name hs68_full_freertos -tcf=hs68_full.tcf -Ml -buildlib_dir /path/to/lib/

      In Makefile:
      MW_HS6X_LIB = /path/to/lib/hs68_full_freertos

Requirements
====================
 * Toolchains:

    Metaware (tested version 2022.09) [here](https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware) or arc_gnu [here](https://github.com/foss-for-synopsys-dwc-arc-processors/toolchain/releases/) (tested version 2023.09.rc2)

 * Simulators:

    nSIM [here](https://www.synopsys.com/cgi-bin/dwarcnsim/req1.cgi) or QEMU [here](https://github.com/foss-for-synopsys-dwc-arc-processors/qemu)


Build
====================

 * For Metaware toolchain:
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS6x_NSIM_QEMU_GCC_MW
    $ make
```
 * For arc_gnu toolchain:
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS6x_NSIM_QEMU_GCC_MW
    $ make TOOLCHAIN=gnu
```
Debug
====================

This example outputs via console through Metaware or MDB debugger. 

 * For Metaware toolchain:
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS6x_NSIM_QEMU_GCC_MW
    $ make debug
```
Use nSIM simulator and debug in MetaWare IDE.

 * For arc_gnu toolchain:

The following step is to launch nSIM simulator (to use QEMU, please replace nsim with qemu) and wait for the connection from gdb.
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS6x_NSIM_QEMU_GCC_MW
    $ make TOOLCHAIN=gnu nsim
```
Then open another terminal and run GNU debugger by following commands:
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS6x_NSIM_QEMU_GCC_MW
    $ make TOOLCHAIN=gnu debug
```
Type c to continue and see the output.

Sample Output
=============

If you are using the **nSIM**, one console will be used to simulate the
project, you will see the following output in the CMD window when the
download is successful.
```
    TimerCounter=1  QueueCounter=4
    TimerCounter=2  QueueCounter=9
    TimerCounter=3  QueueCounter=14
        .................
```
If you are using the **QEMU**, one console will be used to simulate the
project, you will see the following output in the CMD window when the
download is successful.
```
    TimerCounter=1  QueueCounter=4
    TimerCounter=2  QueueCounter=9
    TimerCounter=3  QueueCounter=14
        .................
```