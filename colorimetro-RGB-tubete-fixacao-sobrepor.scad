$fn = 200;

diamLED = 8;
diamLDR = 5;
pino = 2;
raioLED = 2.5;
raioLDR = 2.5;
pinoLED = 1;
pinoLDR = 1;
dist = 3.;
tol = 1;
h = 9;

tuboDiam = 27;

module capelinha(heigh=15,alt=10){
    difference(){
        union(){
            hull(){
                translate([0,0,0]) cube([5,10,alt],center=true);
                translate([0,0,heigh]) rotate([0,90.,0]) cylinder(5,d=10,center=true);
            }
            translate([-4,0,-5+2]) rotate([0,-90.,0]) #cylinder(5,d=4,center=true);// pino
        }
    translate([0,0,heigh]) rotate([0,90.,0]) cylinder(7,d=4,center=true);  //furo
    translate([2,0,heigh]) rotate([0,90.,0]) cylinder(3,d1=4,d2=8,center=true);//scareado
    echo (heigh + 5 - 2 );  // para projeto doa furão da parede, mdf laser cutter etc
    }
}


module aba(diam = 5,dist = 3)
{
   difference(){
        cube([diam + dist , diam + dist ,2],center=true);
        translate([-raioLDR+0.5, 0.0, -3.0]) cylinder(20,d=pino,center=true);
        translate([ raioLDR-0.5, 0.0, -3.0]) cylinder(20, d=pino,center=true);
   }
}

module abaRGB(diam = 5,dist = 3)
{
   difference(){
        cube([diam + dist , diam + dist ,2],center=true);
        translate([-raioLDR, 0.0, -3.0]) cylinder(20,d=1,center=true);
        translate([ raioLDR-1.66, 0.0, -3.0]) cylinder(20, d=1,center=true);
        translate([-raioLDR+1.66, 0.0, -3.0]) cylinder(20,d=1,center=true);
        translate([ raioLDR, 0.0, -3.0]) cylinder(20, d=1,center=true);
   }
}



module scorpo(diam = 10,hh=10)
{
   difference(){
       union(){
            translate([0,0,-tuboDiam/2-6]) minkowski(){
                    cube([diam + 6 -4, diam + 6 -4 ,2.0 + hh],center=true);
                    cylinder(r=2,h=1,center=true);
                    }
            rotate([180,0,0]) translate([0,0,-tuboDiam/2-6]) minkowski(){
                    cube([diam + 6 -4, diam + 6 -4 ,2.0 + hh],center=true);
                    cylinder(r=2,h=1,center=true);
                   }
            rotate([90,0,0]) translate([0,0,-tuboDiam/2-6])  minkowski(){
                    cube([diam + 6 -4, diam + 6 -4 ,2.0 + hh],center=true);
                    cylinder(r=2,h=1,center=true);
                   }
            translate([0,0,0])  rotate([0,90,0]) cylinder(hh+5,d=tuboDiam+4,center=true); // anel
            translate([2,23,0]) rotate([90,0,-90])  capelinha(20);
        }
        rotate([0,90,0]) cylinder(hh+6+4,d=tuboDiam,center=true);  //furo do anel do tubo
        translate([0,0,0]) cylinder(tuboDiam+2*hh+20,d=diam,center=true); // furos da eletronica
        // fiação
        translate([-raioLDR, 0.0, 25.5]) rotate([-90,0,0]) cylinder(20,d=1); //fiacao
        translate([-raioLDR+1.66, 0.0, 25.5]) rotate([-90,0,0]) cylinder(20,d=1); //fiacao
        translate([ raioLDR-1.66, 0.0, 25.5]) rotate([-90,0,0]) cylinder(20, d=1.2);//fiacao
        translate([ raioLDR, 0.0, 25.5]) rotate([-90,0,0]) cylinder(20, d=1.2);//fiacao
        translate([-raioLDR+0.5, 0.0, -25.5]) rotate([-90,0,0]) cylinder(20,d=pino);//fiacao
        translate([ raioLDR-0.5, 0.0, -25.5]) rotate([-90,0,0]) cylinder(20, d=pino);//fiacao
        translate([ 0,20,0]) cube([20,2,3],center=true); // abracadeira vert
        translate([ 0,20,0]) cube([3,2,20],center=true);  // abracadeira hor
        translate([ 0,15,0]) cube([5,2,20],center=true); //fiacao


    }
   translate([0,0, -tuboDiam/2-6 +2])aba(); // suportes da eletronicas
   translate([0,0, +tuboDiam/2+6 +4])abaRGB();
   
}


i=1;
if(i==1) scorpo(diamLED,9);
if(i==1) translate([0,40,0]) capelinha(20);
  