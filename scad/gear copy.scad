/*
File name: SG90 gyro head model
Licence: GNU

Author: Bekir Dağ
Author website: https://bekirdag.com
Author email: bekir@piyote.com
*/

$fn = 100;

module full() {
    color("blue",0.5) { cylinder(5,0.28,0.28);}
}

module exclude() {
    color("green",0.5) { cylinder(5,0.13,0.13);}
}

module all_full(num_of_teeth = 25, r = 2.23) {
    alpha = 360/num_of_teeth;

    for(i=[1:1:num_of_teeth]) {
        x = r*cos(alpha*i);
        y = r*sin(alpha*i);
        translate([x,y,0]) full();
    }
}

module all_exclude(num_of_teeth = 25, r = 2.5) {
    alpha = 360/num_of_teeth;

    for(i=[1:1:num_of_teeth]) {
        x = r*cos(alpha*i);
        y = r*sin(alpha*i);
        translate([x,y,0]) exclude();
    }
}

difference() {
    union(){
        rotate([0,0,11])all_full();
        color("yellow",0.5)cylinder(5,2.42,2.42);
    }
    rotate([0,0,3.8])all_exclude();
}
