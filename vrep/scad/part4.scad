$fn = 100;
board_size = 140;

battery_out = [90,69,15];

        cube([board_size,board_size,4]);


module solar_solder_hole(){
    translate([27.5+x_board_diff,33.5+y_board_diff,16]) cylinder(r=2.5,h=3);
    translate([37.5+x_board_diff,33.5+y_board_diff,16]) cylinder(r=2.5,h=3);    
}

    
    



module screwhole(){
    screw_hole = [10,10,20];
    difference() {
        translate([25,25.5,-13]) color("DarkSlateBlue") cube([10,10,17]);
        just_screw_hole();
    }
    
} 

module just_screw_hole(){
    color("blue") translate([((board_size-battery_out[0])/2+5),((board_size-battery_out[1])/2-5),-18])  cylinder(r=1.75,h=30);   
}

module bigger_screw_hole(){
    color("blue") translate([((board_size-battery_out[0])/2+5),((board_size-battery_out[1])/2-5),-18])  cylinder(r=5,h=30);   
}

module screwhole(){
    screw_hole = [10,10,20];
    difference() {
        translate([25,25.5,-15]) color("DarkSlateBlue") cube([10,10,19]);
//        just_screw_hole();
    }
    
} 


screwhole();
translate([80,0,0]) screwhole();
translate([80,79,0]) screwhole();
translate([0,79,0]) screwhole();



















