/*
Project name: Quadrep for humans
Project url: https://botforhumans.org/projects/quadruped-for-humans
Licence: GNU
Part: Part no#1, Servo wrapper

Author: Bekir Dağ
Author website: https://bekirdag.com
Author email: bekir@piyotecom
*/

$fn = 100;

// top part
difference(){
    union() {
        translate([-1,0,25.8]){
            cube([13.8,35.9,3]);
        }
        translate([5.9,25.3,25.8]) cylinder(3,8,8);
    }

    

    union() {
        color("green") hull()
        {
            translate([5.9,18.8,25.5]) cylinder(5,2.8,2.8);
            translate([5.9,20.8,25.5]) cylinder(5,2.8,2.8);
        }

        translate([5.9,6.5,25.5]) cylinder(5,2.7,2.7);
        
        color("blue") translate([5.9,25.3,25.5]) cylinder(4,6.2,6.2);
    }
    
}



// extension to screw 
color("red") {
    translate([8.2,-5.9,12.7]) {
        difference() {
           translate([0.1,0,-0.5]) cube([2.1,7.4,4.3]);
           rotate([0,90,0]) translate([-1.65,2.2,-0.1]) cylinder(10,1,1);
        }
    }
}

// bottom cylinder
color("red") translate([5.8,25.3,-3])cylinder(3,2.5,2.5);

difference() {
    translate([-1,0,0]) cube([13.8,35.9,3]);
    // bottom screws
    union() {
        color("green") translate([1.8,9.7,-0.1])cylinder(2.8,2.5,0.5);
        color("green") translate([1.8,29.7,-0.1])cylinder(2.8,2.5,0.5);
        color("green") translate([9.8,29.7,-0.1])cylinder(2.8,2.5,0.5);
        color("green") translate([9.8,9.7,-0.1])cylinder(2.8,2.5,0.5);
        
        color("green") translate([1.8,9.7,1.5])cylinder(2,0.8,0.5);
        color("green") translate([1.8,29.7,1.5])cylinder(2,0.8,0.5);
        color("green") translate([9.8,29.7,1.5])cylinder(2,0.8,0.5);
        color("green") translate([9.8,9.7,1.5])cylinder(2,0.8,0.5);
    }
}


// middle part
difference() {
    translate([-1,0,0]) cube([13.8,3,28.7]);

    union() {
        color("blue") translate([-1.5,-0.1,6.7]) cube([14.8,1.6,15.3]);

        
        // hole for extension
        color("pink") translate([3.15,-0.1,9.65])  cube([5.15,10,10]);
        
        
    }
    
    
}


