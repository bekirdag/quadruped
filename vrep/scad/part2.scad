$fn = 100;

difference() {
    union() {
        cube([12,4,24]);
        translate([0,37,0]) cube([12,4,24]);
        cube([12,41,3]);  


    }

}

translate([3.5,18.5,-40]) cube([5,5,40]);
