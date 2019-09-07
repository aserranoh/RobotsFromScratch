
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/wheel-support.dxf");
LOW_HEIGHT = 9.5;
LOW_LAYER = "openscad_low";
HIGH_HEIGHT = 17;
HIGH_LAYER = "openscad_high";
AXIS_LENGTH = 14;
AXIS_RADIUS = 4.75;
AXIS_POS = [0, 13, HIGH_HEIGHT];
BIG_HOLE_LENGTH = 8;
BIG_HOLE_RADIUS = sqrt(pow(AXIS_RADIUS, 2) + pow(HIGH_HEIGHT - LOW_HEIGHT, 2));
SMALL_HOLE_LENGTH = AXIS_LENGTH + 2;
SMALL_HOLE_RADIUS = 1.05;

difference() {
	union() {
		linear_extrude(height = LOW_HEIGHT) {
			import(file = DXF_FILE, layer = LOW_LAYER, $fn=FN);
		}
		linear_extrude(height = HIGH_HEIGHT) {
			import(file = DXF_FILE, layer = HIGH_LAYER, $fn=FN);
		}
		translate(AXIS_POS) {
			rotate(90, [0, 1, 0]) {
				cylinder(AXIS_LENGTH, AXIS_RADIUS, AXIS_RADIUS, center=true, $fn=FN);
			}
		}
	}
	translate(AXIS_POS) {
		rotate(90, [0, 1, 0]) {
			cylinder(BIG_HOLE_LENGTH, BIG_HOLE_RADIUS, BIG_HOLE_RADIUS, center=true, $fn=FN);
			cylinder(SMALL_HOLE_LENGTH, SMALL_HOLE_RADIUS, SMALL_HOLE_RADIUS, center=true, $fn=FN);
		}
	}
}
