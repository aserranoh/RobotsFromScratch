
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/motor-holder.dxf");
BASE_LAYER = "openscad_base";
HOLDER_HEIGHT = 12;
WALLS_LAYER = "openscad_walls";
SCREW_POS_X = 3.5;
SCREW_POS_Y = 9.5;
SCREW_DEEP = 6;
AXIS_RADIUS = 2;
AXIS_POS_Z = 7;
AXIS_HOLE_HEIGHT = 5;

module holder_base() {
	linear_extrude(height = BASE_THICKNESS) {
		import(file = DXF_FILE, layer = BASE_LAYER, $fn=FN);
	}
}

module holder_walls() {
	difference() {
		difference() {
			linear_extrude(height = HOLDER_HEIGHT) {
				import(file = DXF_FILE, layer = WALLS_LAYER, $fn=FN);
			}
			// Substract the screw holes
			for (y = [SCREW_POS_Y, -SCREW_POS_Y]) {
				translate([SCREW_POS_X, y, HOLDER_HEIGHT - SCREW_DEEP]) {
					cylinder(SCREW_DEEP + 1, SCREW_RADIUS, SCREW_RADIUS, $fn=FN);
				}
			}
		}
		// Substract the motor axis hole
		translate([(BASE_THICKNESS + 2)/2 - 1, 0, AXIS_POS_Z]) {
			rotate(90, [0, 1, 0]) {
				cylinder(BASE_THICKNESS + 2, AXIS_RADIUS, AXIS_RADIUS, center=true, $fn=FN);
			}
			translate([0, 0, (AXIS_HOLE_HEIGHT + 1)/2]) {
				cube([BASE_THICKNESS + 2, AXIS_RADIUS * 2, AXIS_HOLE_HEIGHT + 1], center=true);
			}
		}
	}
}

union() {
	holder_base();
	holder_walls();
}
