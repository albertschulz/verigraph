module a();
endmodule

module parent() #(bit ENABLE = 1);
    if (ENABLE) begin
        a i_a();
    end
endmodule