module b();
endmodule;

module a();
    b i_a();
endmodule;

module parent();
    a i_a();
endmodule