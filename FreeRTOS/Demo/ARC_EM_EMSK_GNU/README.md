# How to run this demo

## Hardware and Tool Requirements
- EMSK 2.3 - ARCEM11D core configuration
- ARC GNU IDE 2017.03

## Build and Run in ARC GNU IDE
- Open ARC GNU Eclipse IDE, and use default workspace
- Click `File->Import`, and on the popup dialog, select `General->Existing Projects into Workspace`,
select root directory to be `<FreeRTOS_Root>/FreeRTOS/Demo/ARC_EM_EMSK_GNU`
- Choose the project and import it
- Open the project `Properties` and select `C/C++ Build->Settings`, in the TAB `Tool Settings`, select `Target Processor`, choose the correct tcf file in `TCF path`, choose `<FreeRTOS_Root>\FreeRTOS\Demo\ARC_EM_EMSK_GNU\CoreConfig\23_ARCEM11D\arc_core.tcf`.
- Save the ide project properities.
- Build the IDE Project, and will see output message like this.
```
18:56:09 **** Build of configuration BUILD_23_ARCEM11D for project freertos_demo ****
make all
Building file: C:/Personal/workspace/sourcecode/embARC/freertos/FreeRTOS/Source/portable/Synopsys/ARC/arc_support.S
Invoking: ARC ELF32 GCC Assembler
arc-elf32-gcc -mcpu=em4_fpuda -mlittle-endian -mcode-density -mdiv-rem -mswap -mnorm -mmpy-option=6 -mbarrel-shifter -mfpu=fpuda_all --param l1-cache-size=16384 --param l1-cache-line-size=32 -g3 -gdwarf-2 -x assembler-with-cpp -DMID_COMMON -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\ARC_EM_EMSK_GNU\CoreConfig\23_ARCEM11D" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\Common\drivers\Synopsys\embARC_BSP" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Source\portable\Synopsys\ARC" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Source\include" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\ARC_EM_EMSK_GNU" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\Common\include" -Wall -Wa,-adhlns="Source/portable/Synopsys/ARC/arc_support.o.lst" -c -fmessage-length=0 -MMD -MP -MF"Source/portable/Synopsys/ARC/arc_support.d" -MT"Source/portable/Synopsys/ARC/arc_support.o" -o "Source/portable/Synopsys/ARC/arc_support.o" "C:/Personal/workspace/sourcecode/embARC/freertos/FreeRTOS/Source/portable/Synopsys/ARC/arc_support.S"
Finished building: C:/Personal/workspace/sourcecode/embARC/freertos/FreeRTOS/Source/portable/Synopsys/ARC/arc_support.S

......SKIP BUILD MESSGAE.........

Building file: ../main.c
Invoking: ARC ELF32 GCC C Compiler
arc-elf32-gcc -mcpu=em4_fpuda -mlittle-endian -mcode-density -mdiv-rem -mswap -mnorm -mmpy-option=6 -mbarrel-shifter -mfpu=fpuda_all --param l1-cache-size=16384 --param l1-cache-line-size=32 -g3 -gdwarf-2 -DMID_COMMON -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\ARC_EM_EMSK_GNU\CoreConfig\23_ARCEM11D" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\Common\drivers\Synopsys\embARC_BSP" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Source\portable\Synopsys\ARC" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Source\include" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\ARC_EM_EMSK_GNU" -I"C:\Personal\workspace\sourcecode\embARC\freertos\FreeRTOS\Demo\Common\include" -O2 -Wall -Wa,-adhlns="main.o.lst" -c -fmessage-length=0 -MMD -MP -MF"main.d" -MT"main.o" -o "main.o" "../main.c"
Finished building: ../main.c

Building target: freertos_demo.elf
Invoking: ARC ELF32 GCC C Linker
arc-elf32-gcc -mcpu=em4_fpuda -mlittle-endian -mcode-density -mdiv-rem -mswap -mnorm -mmpy-option=6 -mbarrel-shifter -mfpu=fpuda_all --param l1-cache-size=16384 --param l1-cache-line-size=32 -g3 -gdwarf-2 -T"../CoreConfig/23_ARCEM11D/arc_core.ld" -nostartfiles -Wl,-Map,freertos_demo.map --specs=nsim.specs -o "freertos_demo.elf"  ./Source/portable/Synopsys/ARC/arc_support.o ./Source/portable/Synopsys/ARC/port.o  ./Source/portable/MemMang/heap_2.o  ./Source/croutine.o ./Source/event_groups.o ./Source/list.o ./Source/queue.o ./Source/tasks.o ./Source/timers.o  ./Serial/serial.o ./Serial/serialISR.o  ./ParTest/ParTest.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/device/designware/uart/dw_uart.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/device/designware/iic/dw_iic.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/device/designware/gpio/dw_gpio.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/common/console_io.o ./Demo/Common/drivers/Synopsys/embARC_BSP/common/xprintf.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/uart/dw_uart_obj.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/iic/dw_iic_obj.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/gpio/dw_gpio_obj.o ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/gpio/emsk_gpio.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/common/emsk_init.o ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/common/emsk_timer.o ./Demo/Common/drivers/Synopsys/embARC_BSP/board/emsk/common/mux.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/board/board.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/arc/startup/arc_cxx_support.o ./Demo/Common/drivers/Synopsys/embARC_BSP/arc/startup/arc_startup.o  ./Demo/Common/drivers/Synopsys/embARC_BSP/arc/arc_cache.o ./Demo/Common/drivers/Synopsys/embARC_BSP/arc/arc_exc_asm.o ./Demo/Common/drivers/Synopsys/embARC_BSP/arc/arc_exception.o ./Demo/Common/drivers/Synopsys/embARC_BSP/arc/arc_timer.o  ./Demo/Common/Minimal/BlockQ.o ./Demo/Common/Minimal/PollQ.o ./Demo/Common/Minimal/comtest.o ./Demo/Common/Minimal/dynamic.o ./Demo/Common/Minimal/flash.o ./Demo/Common/Minimal/flop.o ./Demo/Common/Minimal/integer.o ./Demo/Common/Minimal/semtest.o  ./main.o   -lm
Finished building target: freertos_demo.elf

Invoking: ARC ELF32 GNU Print Size
arc-elf32-size  --format=berkeley -x -t freertos_demo.elf
   text    data     bss     dec     hex filename
 0xb030   0x4e8  0xa5d4   88812   15aec freertos_demo.elf
 0xb030   0x4e8  0xa5d4   88812   15aec (TOTALS)
Finished building: freertos_demo.siz


19:00:31 Build Finished (took 4m:21s.783ms)
```
- When the ide project is built successfully, then open the debug configuration dialog, and create a debug configuration, and choose the elf file, and set the debugger to be openocd with EM Starter Kit v2, and debug it and run.

## Build and run in command line
- Open command terminal in `<FreeRTOS_Root>/FreeRTOS/Demo/ARC_EM_EMSK_GNU`
- Edit the `Makefile` in this folder, change the `OPENOCD_SCRIPT_ROOT` definition in this makefile to the correct place where your openocd configuration root located.
- Make sure `arc-elf32-gcc` is available in command line.
- Type `make` to build this example
- Type `make run` to run this example
