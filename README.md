# verigraph - SystemVerilog Dependency Graphs

> Important: This project is still under construction!

Convert SystemVerilog Code into GraphViz Graph

![Graph for example/top.sv](example/top.svg)

```systemverilog
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
```

## Usage

```bash
$ verigraph p top.sv | dot -Tsvg -o top.svg
```

## License

verigraph is licensed under the MIT license:

> Copyright 2020 Albert Schulz

> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.