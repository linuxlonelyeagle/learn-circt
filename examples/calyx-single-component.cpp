#include "Vcontrol_identity.h"
#include "verilated_vcd_c.h"
#include <iostream>

int main() {
  auto id = new Vcontrol_identity;
  Verilated::traceEverOn(true);
  VerilatedVcdC *trace = new VerilatedVcdC;
  id->trace(trace, 5);
  trace->open("waveform.vcd");
  id->clk = 1;
  for (int in = 0; in < 5; ++in) { 
    id->clk ^= 1;
    id->in = in;
    id->go = 1;
    id->eval();
    trace->dump(in);
    std::cout << id->out << std::endl;
  }
  trace->close();
  delete trace;
  delete id;
  return 0;
}
