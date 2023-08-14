calyx.component @main(%in: i32, %go: i1 {go}, %clk: i1 {clk}, %reset: i1 {reset}) -> (%out: i32, %done: i1 {done}) {
  %r.in, %r.write_en, %r.clk, %r.reset, %r.out, %r.done = calyx.register @r : i32, i1, i1, i1, i32, i1
  calyx.wires {
    calyx.assign %r.in = %in : i32
    calyx.assign %r.clk = %clk : i1
    calyx.assign %out = %r.out : i32
    calyx.assign %r.reset = %reset : i1
    calyx.assign %r.write_en = %go : i1
  }
  calyx.control {
  }
}