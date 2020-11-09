module a();
endmodule

module parent();
    if (1) begin
        if (1) begin
            a i_a();
        end
    end
endmodule