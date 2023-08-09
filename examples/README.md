# Simulation of hardware using Verilator
I didn't add tests for running c++ code to the makefile because the verilog code generated so far needs to be separated manually, 
here are some demos.
## Separate the log.sv file 
Let's take `calyx-single-component` as an example.
```
// Generated by CIRCT unknown git version
`include "fsm_enum_typedefs.sv"	// ./calyx-single-component.mlir
module control_identity(	// ./calyx-single-component.mlir:14:3
  input  in0,
         in1,
         clk,
         rst,
  output out0,
         out1
);

     control_identity_state_t to_fsm_entry;	// ./calyx-single-component.mlir:14:3
  assign to_fsm_entry = control_identity_state_t_fsm_entry;	// ./calyx-single-component.mlir:14:3
     control_identity_state_t to_fsm_exit;	// ./calyx-single-component.mlir:14:3
  assign to_fsm_exit = control_identity_state_t_fsm_exit;	// ./calyx-single-component.mlir:14:3
     control_identity_state_t to_seq_0_save;	// ./calyx-single-component.mlir:14:3
  assign to_seq_0_save = control_identity_state_t_seq_0_save;	// ./calyx-single-component.mlir:14:3
     control_identity_state_t state_next;	// ./calyx-single-component.mlir:14:3
     control_identity_state_t state_reg;	// ./calyx-single-component.mlir:14:3
  always_ff @(posedge clk) begin	// ./calyx-single-component.mlir:14:3
    if (rst)	// ./calyx-single-component.mlir:14:3
      state_reg <= to_fsm_entry;	// ./calyx-single-component.mlir:14:3
    else	// ./calyx-single-component.mlir:14:3
      state_reg <= state_next;	// ./calyx-single-component.mlir:14:3
  end // always_ff @(posedge)
  reg                          output_0;	// ./calyx-single-component.mlir:14:3
  reg                          output_1;	// ./calyx-single-component.mlir:14:3
  always_comb begin	// ./calyx-single-component.mlir:14:3
    case (state_reg)	// ./calyx-single-component.mlir:14:3
      control_identity_state_t_fsm_entry: begin
        state_next = in1 ? to_seq_0_save : to_fsm_entry;	// ./calyx-single-component.mlir:14:3, :15:5
        output_0 = 1'h0;	// ./calyx-single-component.mlir:14:3
        output_1 = 1'h0;	// ./calyx-single-component.mlir:14:3
      end
      control_identity_state_t_fsm_exit: begin
        state_next = to_fsm_exit;	// ./calyx-single-component.mlir:14:3
        output_0 = 1'h0;	// ./calyx-single-component.mlir:14:3
        output_1 = 1'h1;	// ./calyx-single-component.mlir:14:3
      end
      control_identity_state_t_seq_0_save: begin
        state_next = in0 ? to_fsm_exit : to_seq_0_save;	// ./calyx-single-component.mlir:14:3, :16:7
        output_0 = 1'h1;	// ./calyx-single-component.mlir:14:3
        output_1 = 1'h0;	// ./calyx-single-component.mlir:14:3
      end
      default: begin
      end
    endcase	// ./calyx-single-component.mlir:14:3
  end // always_comb
  assign out0 = output_0;	// ./calyx-single-component.mlir:14:3
  assign out1 = output_1;	// ./calyx-single-component.mlir:14:3
endmodule

module identity(	// ./calyx-single-component.mlir:1:1
  input  [31:0] in,
  input         go,
                clk,
                reset,
  output [31:0] out,
  output        done
);

  wire        _controller_out0;	// ./calyx-single-component.mlir:14:3
  wire        r_reset = 1'bz;	// ./calyx-single-component.mlir:2:59
  reg         r_done_reg;	// ./calyx-single-component.mlir:2:59
  reg  [31:0] r_reg;	// ./calyx-single-component.mlir:2:59
  always_ff @(posedge clk) begin	// ./calyx-single-component.mlir:2:59
    if (r_reset) begin	// ./calyx-single-component.mlir:2:59
      r_done_reg <= 1'h0;	// ./calyx-single-component.mlir:2:59
      r_reg <= 32'h0;	// ./calyx-single-component.mlir:2:59
    end
    else begin	// ./calyx-single-component.mlir:2:59
      r_done_reg <= _controller_out0;	// ./calyx-single-component.mlir:2:59, :14:3
      if (_controller_out0 & ~r_done_reg)	// ./calyx-single-component.mlir:2:59, :14:3
        r_reg <= _controller_out0 ? in : 32'h0;	// ./calyx-single-component.mlir:2:59, :7:7, :14:3
    end
  end // always_ff @(posedge)
  control_identity controller (	// ./calyx-single-component.mlir:14:3
    .in0  (r_done_reg),	// ./calyx-single-component.mlir:2:59
    .in1  (go),
    .clk  (clk),
    .rst  (reset),
    .out0 (_controller_out0),
    .out1 (done)
  );
  assign out = r_reg;	// ./calyx-single-component.mlir:1:1, :2:59
endmodule


// ----- 8< ----- FILE "fsm_enum_typedefs.sv" ----- 8< -----

// Generated by CIRCT unknown git version
`ifndef _TYPESCOPE_fsm_enum_typedecls
`define _TYPESCOPE_fsm_enum_typedecls
  typedef
    enum bit [1:0] {control_identity_state_t_fsm_entry, control_identity_state_t_fsm_exit, control_identity_state_t_seq_0_save}
    control_identity_state_t;	// ./calyx-single-component.mlir:14:3
`endif // _TYPESCOPE_fsm_enum_typedecls
```
You can see the code `include "fsm_enum_typedefs.sv"` and `FILE "fsm_enum_typedefs.sv"`, Then split the above into two, one that
holds the main logic of the code and one called `fsm_enum_typedefs.sv`.
## Compiling c++ code
```
$ verilator -cc control_identity.sv -exe xxx.cpp --exe --build -j 0 --trace
$ cd obj_dir
$ ./xxx
```