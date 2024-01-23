# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_AXILiteS {
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
inputs { 
	dir I
	width 32
	depth 10
	mode ap_memory
	offset 64
	offset_end 127
}
depth { 
	dir I
	width 16
	depth 1
	mode ap_none
	offset 128
	offset_end 135
}
out_r { 
	dir O
	width 32
	depth 10
	mode ap_memory
	offset 192
	offset_end 255
}
out_correct { 
	dir O
	width 1
	depth 1
	mode ap_vld
	offset 256
	offset_end 263
}
}
dict set axilite_register_dict AXILiteS $port_AXILiteS


