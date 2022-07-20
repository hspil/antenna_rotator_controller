include <YAPPgenerator_v15.scad>;

printBaseShell = false;
printLidShell  = true;

wallThickness      = 2;
basePlaneThickness = 2;
lidPlaneThickness  = 2;

baseWallHeight      = 7;
lidWallHeight       = 13;

//radius of box edges
roundRadius = 1;

pcbLength           = 70;
pcbWidth            = 30;
pcbThickness        = 1.5;

// padding between pcb and inside wall
paddingFront        = 1;
paddingBack         = 1;
paddingRight        = 1;
paddingLeft         = 1;

ridgeHeight = 3;
ridgeSlack = 0.2;

//-- pcb_standoffs  -- origin is pcb[0,0,0]
// (0) = posx
// (1) = posy
// (2) = { yappBoth | yappLidOnly | yappBaseOnly }
// (3) = { yappHole, YappPin }
pcbStands = [
             [2, 2, yappBaseOnly],
             [2, pcbWidth - 2, yappBaseOnly],
             [pcbLength - 2, 2, yappBaseOnly],
             [pcbLength - 2, pcbWidth - 2, yappBaseOnly]
            ];

standoffHeight = 4;
pinDiameter = 1.75;
standoffDiameter = 4;

cutoutsFront = [
                [10, 2, 12, 8, 0, yappRectangle]
               ];

cutoutsLeft = [
               [30, 1, 6, 0, 0, yappCircle]
              ];

//-- snap Joins -- origin = box[x0,y0]
// (0) = posx | posy
// (1) = width
// (2..5) = yappLeft / yappRight / yappFront / yappBack (one or more)
// (n) = { yappSymmetric }
snapJoins   =     [
                    [10, 5, yappLeft, yappRight, yappSymmetric]
                ];

labelsPlane = [
               [5, 28, 0, "lid", "Arial:style=bold", 5, "Comp. Iface. for:" ],
               [5, 20, 0, "lid", "Arial:style=bold", 7, "Yaesu G-5400" ],
               [5, 28, 0, "base", "Arial:style=bold", 4, "Case designed with YAPP" ]
              ];

YAPPgenerate();