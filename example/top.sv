package   pkg;       endpackage
interface axi_if;    endinterface
module    fifo();    endmodule
module    decoder(); endmodule

module top;
    import pkg::*;
    axi_if axi();
    fifo fifo_i();
    decoder decoder_i();
endmodule