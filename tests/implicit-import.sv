package pkg;
    localparam PARAM = 42;
endpackage

module parent();
    localparam P = pkg::PARAM;
endmodule