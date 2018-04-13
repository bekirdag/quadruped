$fn = 100;
board_size = 140;



battery_out = [90,69,2];

difference(){
    translate([0,0,0]) cube(battery_out);    
    
    union(){
        translate([0.5,0.5,1]) cube([(battery_out[0]-1),(battery_out[1]-1),(battery_out[1]-1)]);
        
        //rPi screw holes
        translate([31,5.5,-0.1]) cylinder(r=1,h=2);
        translate([31,63.5,-0.1]) cylinder(r=1,h=2);
        translate([8,5.5,-0.1]) cylinder(r=1,h=2);
        translate([8,63.5,-0.1]) cylinder(r=1,h=2);
        
        // adafruit screw holes
        translate([40,62.5,-0.1]) cylinder(r=1,h=2);
        translate([59,62.5,-0.1]) cylinder(r=1,h=2);
        
        translate([40,6.5,-0.1]) cylinder(r=1,h=2);
        translate([59,6.5,-0.1]) cylinder(r=1,h=2);
        
        // gyro screw holes
        translate([69,63.5,-0.1]) cylinder(r=1,h=2);
        translate([84.5,63.5,-0.1]) cylinder(r=1,h=2);
    }

}



module screwhole(){
    screw_hole = [10,10,0];
    difference() {
        translate([0,-10,0]) color("pink") cube([10,10,1]);
        color("blue") translate([5,-5,-0.1])  cylinder(r=1.75,h=21);    
    }

} 


screwhole();
translate([80,0,0]) screwhole();
translate([80,79,0]) screwhole();
translate([0,79,0]) screwhole();

// seperate lines
translate([35,0,1]) cube([1,69,1]);
translate([63,0,1]) cube([1,69,1]);

translate([69,0,1]) cube([1,48,1]);
translate([69,47,1]) cube([21,1,1]);

