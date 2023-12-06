#include <arc_feature_config.h>

ASSERT(REGION_ICCM_SIZE, "invalid ICCM size")
ASSERT(REGION_ICCM_SIZE, "invalid DCCM size")
MEMORY
{
	REGION_ICCM :		ORIGIN = REGION_ICCM_START,	LENGTH = REGION_ICCM_SIZE
	REGION_DCCM :		ORIGIN = REGION_DCCM_START,	LENGTH = REGION_DCCM_SIZE
}

ENTRY(_start)

SECTIONS
{
	.init :
	{
		_f_init = .;
		KEEP (*(.init_vector .init_vector.*))
		KEEP (*(.init_bootstrap .init_bootstrap.*))
		_e_init = .;
	} > REGION_ROM

	.vector : ALIGN(1024)
	{
		_f_vector = .;
		*(.vector .vector.*)
		_e_vector = .;
	} > REGION_ROM

	.text : ALIGN(4)
	{
		_f_text = .;
		*(.text .text.* .gnu.linkonce.t.*)
		_e_text = .;
	} > REGION_ROM

	.rodata : ALIGN(4)
	{
		_f_rodata = .;
		*(.rodata .rodata.* .gnu.linkonce.r.*)
		_e_rodata = .;
	} > REGION_ROM

	.data : ALIGN(4)
	{
		_f_data = .;
		*(.data .data.* .gnu.linkonce.d.*)
		_f_sdata = .;
		__SDATA_BEGIN__ = .;
		*(.sdata .sdata.* .gnu.linkonce.s.*)
		PROVIDE (__sbss_start = .);
		PROVIDE (___sbss_start = .);
		_f_sbss = .;
		*(.dynsbss)
		*(.sbss .sbss.* .gnu.linkonce.sb.*)
		*(.scommon)
		_e_sbss = .;
		PROVIDE (__sbss_end = .);
		PROVIDE (___sbss_end = .);
		_e_sdata = .;
		_e_data = .;
	} > REGION_RAM AT > REGION_ROM

	.bss (NOLOAD) : ALIGN(8)
	{
		_f_bss = .;
		*(.dynbss)
		*(.bss .bss.* .gnu.linkonce.b.*)
		*(COMMON)
		_e_bss = .;
	} > REGION_RAM

	.stack (NOLOAD) :
	{
		. = ALIGN(4);
		_f_stack = .;
		. = . + _STACKSIZE;
		_e_stack = .;
	} > REGION_RAM

	.heap (NOLOAD) :
	{
		. = ALIGN(4);
		__start_heap = . ;
		_f_heap = .;
		. = . + _HEAPSIZE;
		_e_heap = .;
		__end_heap = . ;
	} > REGION_RAM

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}
