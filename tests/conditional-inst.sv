module a();
endmodule

module parent() #(bit ENABLE);
    if (ENABLE) begin
        a i_a();
    end
endmodule