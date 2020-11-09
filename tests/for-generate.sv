module a();
endmodule

module parent();
    for(genvar i = 0; i < 2; i++) begin
        a i_a();
    end
endmodule