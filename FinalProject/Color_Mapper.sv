//-------------------------------------------------------------------------
//    Color_Mapper.sv                                                    --
//    JiHo Han								 --
//                                                                       --
//    For use with ECE 385 Final Project                                 --
//    University of Illinois ECE Department                              --
//-------------------------------------------------------------------------

// color_mapper: Decide which color to be output to VGA for each pixel.
module  color_mapper ( input              is_graph,            // Whether current pixel belongs to the graph 
                                                              //   or background (computed in graph.sv)
                       input        [9:0] DrawX, DrawY,       // Current pixel coordinates
                       output logic [7:0] VGA_R, VGA_G, VGA_B // VGA RGB output
                     );
    
    logic [7:0] Red, Green, Blue;
    
    // Output colors to VGA
    assign VGA_R = Red;
    assign VGA_G = Green;
    assign VGA_B = Blue;
    
    // Assign color based on is_ball signal
    always_comb
    begin
        if (is_graph == 1'b1) 
        begin
            // White graph
            Red = 8'hff;
            Green = 8'hff;
            Blue = 8'hff;
        end
        else 
        begin
            Red = 8'h00; 
            Green = 8'h00;
            Blue = 8'h00;
        end
    end 
    
endmodule
