#!/bin/bash
CIRCT_OPT := ../circt/build/bin/circt-opt

calyx-single-component-export-verilog:
		@${CIRCT_OPT} ./calyx-single-component.mlir \
		-lower-calyx-to-fsm -materialize-calyx-to-fsm \
		-calyx-remove-groups-fsm -lower-calyx-to-hw \
		-convert-fsm-to-sv -lower-hw-to-sv -lower-seq-to-sv \
		-lower-hwarith-to-hw -hw-specialize -hw-cleanup -cse \
		-canonicalize -hw-legalize-modules -prettify-verilog \
		-export-verilog > log.sv
