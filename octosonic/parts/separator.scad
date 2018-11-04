
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/separator.dxf");
BASE_LAYER = "openscad_base";
SEPARATOR_HEIGHT = 16;
BODY_LAYER = "openscad_body";
SCREW_POS_X = 7.5;
SCREW_POS_Y = 16.5;
SCREW_DEEP = 8;

module base() {
	linear_extrude(height = BASE_THICKNESS) {
		import(file = DXF_FILE, layer = BASE_LAYER, $fn=FN);
	}
}

module body() {
	difference() {
		linear_extrude(height = SEPARATOR_HEIGHT) {
			import(file = DXF_FILE, layer = BODY_LAYER, $fn=FN);
		}
		// Substract the screw holes
		for (y = [SCREW_POS_Y, -SCREW_POS_Y]) {
			translate([SCREW_POS_X, y, SEPARATOR_HEIGHT - SCREW_DEEP]) {
				cylinder(SCREW_DEEP + 1, SCREW_RADIUS, SCREW_RADIUS, $fn=FN);
			}
		}
	}
}

union() {
	base();
	body();
}