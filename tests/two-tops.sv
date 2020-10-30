module a();
endmodule;

module b();
endmodule;

module mother();
    a i_a();
endmodule

module father();
    b i_a();
endmodule