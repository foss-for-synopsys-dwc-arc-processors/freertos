FreeRTOS SMP Demo for ARCv3 HS5x machine emulated on Metaware/MDB
====================

Overview
====================
 This example demonstrates basic FreeRTOS task usage in an SMP context, configured to run on 4 cores.
 Note: this DEMO only supports TIMER0 and doesn't support dynamic memory management.

Requirements
====================
 * Toolchain:

    Metaware [here](https://www.synopsys.com/dw/ipdir.php?ds=sw_metaware)


Build
====================

 * Using the Metaware toolchain:
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS5x_SMP
    $ make
```
Debug
====================

This example outputs via console through Metaware or MDB debugger. 

 * Using the Metaware toolchain:
```
    $ cd <FreeRTOS_root>/FreeRTOS/Demo/ARCv3_HS5x_SMP
    $ make debug
```
Sample Output
=============

You will see the following output in the CMD window when the download is successful. Core number may not
be the same as shown here because the tasks can run on any core.
```
    TaskA running on Core 3 [Times switched:   1]
    TaskA running on Core 1 [Times switched:   2]
    TaskA running on Core 1 [Times switched:   3]
    TaskB running on Core 0 [Times switched:   1]
    TaskC running on Core 3 [Times switched:   1]
    TaskB running on Core 1 [Times switched:   2]
    TaskA running on Core 0 [Times switched:   4]
    TaskA running on Core 0 [Times switched:   5]
    TaskA running on Core 1 [Times switched:   6]
    TaskB running on Core 0 [Times switched:   3]
    TaskA running on Core 1 [Times switched:   7]
    TaskA running on Core 2 [Times switched:   8]
    TaskB running on Core 1 [Times switched:   4]
    TaskD running on Core 3 [Times switched:   1]
        .................
```