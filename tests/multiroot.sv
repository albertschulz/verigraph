module a();
endmodule;

module b();
endmodule;

module root() #(bit ENABLE);
    if (ENABLE) begin
        a i_a();
    end
    else begin
        b i_b();
    end
endmodule

module parent();

    root i_root_a(.ENABLE(0));
    root i_root_b(.ENABLE(1));

endmodule
