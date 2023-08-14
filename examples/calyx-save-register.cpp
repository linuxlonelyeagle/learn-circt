#include "Vsave__02dregister.h"
#include "verilated_vcd_c.h"
#include <memory>
#include <iostream>

int main() {
  auto save = new Vsave__02dregister();
  Verilated::traceEverOn(true);
  VerilatedVcdC *trace = new VerilatedVcdC;
  save->trace(trace, 5);
  trace->open("waveform.vcd");
  int tmp = 0;
  save->clk = 1;
  for (int in = 0; in < 10; ++in) { 
    save->clk ^= 1;
    save->in = in;
    save->go = 1;
    save->eval();
    trace->dump(in);
    std::cout << save->out << std::endl;    
    // Reset component.
    if (tmp > 0) {
      -- tmp;
      save->reset = 0;
    }
    if (save->out != 0) {
      save->reset = 1;
      tmp++;
    }
  }
  trace->close();
  delete trace;
  delete save;
  return 0;
}
