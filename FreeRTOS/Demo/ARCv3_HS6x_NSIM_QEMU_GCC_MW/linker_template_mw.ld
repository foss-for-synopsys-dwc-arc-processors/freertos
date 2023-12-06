#include <arc_feature_config.h>

MEMORY {
#if (REGION_ICCM_SIZE != 0)
	REGION_ICCM :		ORIGIN = REGION_ICCM_START,	LENGTH = REGION_ICCM_SIZE
#endif
#if (REGION_DCCM_SIZE !=0)
	REGION_DCCM :		ORIGIN = REGION_DCCM_START,	LENGTH = REGION_DCCM_SIZE
#endif
}

ENTRY(_start)

SECTIONS {

	GROUP : {
		.init_bootstrap:{
			_f_init = .;
			*(.init_vector .init_vector.*)
			*(.init_bootstrap .init_bootstrap.*)
			_e_init = .;
		}
		.vector ALIGN(1024): {
			_f_vector = .;
			*(.vector .vector.*)
			_e_vector = .;
		}
	} > REGION_ROM

	GROUP : {

		.text ALIGN(4): {
			_f_text = .;
			*(TYPE text)
			*(.text*)
			_e_text = .;
		}

		.rodata  ALIGN(4): {
			_f_rodata = .;
			*(TYPE lit)
			_e_rodata = .;
		}

	} > REGION_ROM


	GROUP : {
		.data ALIGN(8): {
			_f_data = .;
			_f_sdata = .;
			*(.sdata)
			*(.sbss)
			_e_sdata = .;
			*(TYPE data)
		}
		.tls ALIGN(8): {
			*(.tls*)
			_e_data = .;
		}
	} > REGION_RAM

	GROUP (NOLOAD) : {
		.bss ALIGN(8): {
			_f_bss = .;
			*(TYPE bss)
			_e_bss = .;
		}
		.stack ALIGN(4) SIZE(_STACKSIZE): {}
		.heap? ALIGN(4) SIZE(_HEAPSIZE): {}
	} > REGION_RAM

	_f_stack = ADDR(.stack);
	_e_stack = ADDR(.stack) + SIZEOF(.stack);
	_f_heap = ADDR(.heap);
	_e_heap = ADDR(.heap) + SIZEOF(.heap);

	_load_addr_text = LOADADDR(.text);
	_load_addr_rodata = LOADADDR(.rodata);
	_load_addr_data = LOADADDR(.data);
}
