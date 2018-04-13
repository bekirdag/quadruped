$fn = 100;
board_size = 140;


cube([board_size,board_size,4]);


battery_out = [90,90,35];

difference(){
    translate([(board_size-battery_out[0])/2,(board_size-battery_out[1])/2,1]) cube(battery_out);
    
    battery_size = [20,66,22];
    

}

translate([0,0,36]) cube([board_size,board_size,4]);


