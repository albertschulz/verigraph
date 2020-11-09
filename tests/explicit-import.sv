package pkg_a;
endpackage

package pkg_b;
    localparam PARAM = 42;
endpackage

module parent();
    import pkg_a::*;
    import pkg_b::PARAM;
endmodule