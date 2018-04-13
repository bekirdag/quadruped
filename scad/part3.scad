$fn = 100;
board_size = 140;

difference() {
    cube([board_size,board_size,4]);
    union() {
        for (a =[0:1:3])
        {
            table_size = board_size-20;
            b = (a==1 || a== 0) ? 0 : 1;
            c = (a==3 || a== 0) ? 0 : 1;
            x = 10+table_size*b;
            y = 10+table_size*c;
            echo("x value", x," y value", y);
            translate([x,y,2]) cylinder(6,2.8,2.8);    
        }
        color("red") translate([20,-0.5,1]) cube([100,141,4]);
        color("red") translate([-0.5,20,1]) cube([141,100,4]);
    }
}

battery_out = [90,69,20];

difference(){
    translate([(board_size-battery_out[0])/2,(board_size-battery_out[1])/2,1]) cube(battery_out);
    
    battery_size = [20,66,22];
    
    union() {
        for(i=[0:1:3]) 
        {
            translate([((board_size-battery_out[0])/2+2)+i*(battery_size[0]+2),(board_size-battery_size[1])/2,1]) cube(battery_size);
            translate([((board_size-battery_out[0])/2+battery_size[0]/2+2)+i*(battery_size[0]+2),(board_size-battery_size[1])/2+0.1,1+battery_out[2]/2]) rotate([90,0,0])cylinder(5,2,2);
            translate([((board_size-battery_out[0])/2+battery_size[0]/2+2)+i*(battery_size[0]+2),(board_size-battery_size[1])/2+battery_size[1]+4,1+battery_out[2]/2]) rotate([90,0,0])cylinder(5,2,2);
            
        }   
    }
}

module screwhole(){
    screw_hole = [10,10,20];
    difference() {
        translate([25,25.5,1]) color("pink") cube([10,10,20]);
        color("blue") translate([((board_size-battery_out[0])/2+5),((board_size-battery_out[1])/2-5),1])  cylinder(r=1.75,h=21);    
    }

} 

screwhole();
translate([80,0,0]) screwhole();
translate([80,79,0]) screwhole();
translate([0,79,0]) screwhole();
