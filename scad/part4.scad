$fn = 100;
board_size = 140;

battery_out = [90,69,15];

difference() {
    union(){
        cube([board_size,board_size,4]);
        color("green") translate([(board_size-battery_out[0])/2,(board_size-battery_out[1])/2,3]) cube(battery_out);
        color("pink") translate([0,0,17]) cube([board_size,board_size,1]);
    }
    
    union() {
        for (a =[0:1:3])
        {
            table_size = board_size-20;
            b = (a==1 || a== 0) ? 0 : 1;
            c = (a==3 || a== 0) ? 0 : 1;
            x = 10+table_size*b;
            y = 10+table_size*c;
             translate([x,y,2])  rotate([0,0,-45-90*a]){
                color("green") hull() 
                {
                    translate([0,0.4,0]) cylinder(6,4,4);
                    translate([0,15,0]) cylinder(6,2.1,2.1);
                    
                }    
//                color("red") translate([0,15,0]) cylinder(6,3.8,3.8);    
            }
            translate([x,y,-1]) color("red") translate([0,0,0]) cylinder(28,3.8,3.8);
        }
        color("red") translate([25,-0.5,-1]) cube([90,141,4]);
        color("red") translate([-0.5,25,-1]) cube([141,90,4]);
        color("blue") translate([(board_size-battery_out[0])/2+1,(board_size-battery_out[1])/2+1,2]) cube([(battery_out[0]-2),(battery_out[1]-2),(battery_out[2])]);
        

        solar_solder_hole();
        translate([0,60,0]) solar_solder_hole();
        translate([62,60,0]) solar_solder_hole();
        translate([62,0,0]) solar_solder_hole();    

        translate([0,0,20]) bigger_screw_hole();
        translate([80,0,20]) bigger_screw_hole();
        translate([80,79,20]) bigger_screw_hole();
        translate([0,79,20]) bigger_screw_hole();
        
    }
}

module solar_solder_hole(){
    translate([27.5+x_board_diff,33.5+y_board_diff,16]) cylinder(r=2.5,h=3);
    translate([37.5+x_board_diff,33.5+y_board_diff,16]) cylinder(r=2.5,h=3);    
}

for (a =[0:1:3])
{    
    table_size = board_size-41;
    b = (a==1 || a== 0) ? 0 : 1;
    c = (a==3 || a== 0) ? 0 : 1;
    x = 20.5+table_size*b;
    y = 20.5+table_size*c;
    color("blue") translate([x,y,4.6])  rotate([0,0,-45-90*a]) cube([8,6.2,1.5], center=true);   
}        
    
module polar_holder() {
    translate([5,1,20]) {
        cube([10,2,4], center = true);
        translate([0,1,2.7]) cube([10,4,2], center = true);
    }   
}
solar_panel_size = [60,60,2.5];
x_board_diff = (board_size-solar_panel_size[0]*2)/3;
x_pos = x_board_diff+solar_panel_size[0]/2;

y_board_diff = (board_size-solar_panel_size[1]*2)/3;
y_pos = y_board_diff+solar_panel_size[1];

module polar_y_set(){
    polar_holder();
    translate([10,5+solar_panel_size[1],0]) rotate([0,0,180]) polar_holder();
}

module polar_y_double_set() {
    translate([x_pos,y_board_diff,0]) polar_y_set();
    translate([x_pos,y_board_diff+solar_panel_size[1]+3,0]) polar_y_set();
}

module polar_y_complete_set(){
    polar_y_double_set();
    translate([solar_panel_size[0]-5,0,0]) polar_y_double_set();
}

polar_y_complete_set();
translate([140,0,0]) rotate([0,0,90]) polar_y_complete_set();

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

screwhole();
translate([80,0,0]) screwhole();
translate([80,79,0]) screwhole();
translate([0,79,0]) screwhole();




















