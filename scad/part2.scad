$fn = 100;

difference() {
    union() {
        cube([12,4,18]);
        translate([0,37,0]) cube([12,4,18]);
        cube([12,41,3]);  
        color("pink") translate([6,4,18]) rotate([90,0,0]) cylinder(4,6,6);  
        color("pink") translate([6,41,18]) rotate([90,0,0]) cylinder(4,6,6);  

    }
    
    union() {
        translate([6,2,3]) rotate([90,0,0]) color("green") hull()
        {
            translate([0,0.4,0]) cylinder(6,2.1,2.1);
            translate([0,15,0]) cylinder(6,4,4);
        }    
        translate([6,5,18]) rotate([90,0,0]) cylinder(6,3.8,3.8);
        
        translate([6,39,18]) rotate([90,0,0]) cylinder(6,2.8,2.8);
//        translate([6,4.5,3]) rotate([90,0,0]) cylinder(3,3,3); 
        translate([3,1.1,3]) cube([6,3,2]);       

    }
}

//stopper
translate([3,-2,1]) cube([6,2,4]);

//leg
color("red")translate([6,21,-40]) cylinder(40,2.5,2.5);

//translate([6,21,-51]) color("blue") sphere(5);

