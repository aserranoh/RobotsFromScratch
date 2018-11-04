
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/octosonic.dxf");
BASE_LAYER = "openscad_base";
SUPPORTS_HEIGHT = 10.5;
SUPPORTS_LAYER = "openscad_supports";
BATTERY_BOX_HEIGHT = 19;
BATTERY_BOX_LAYER = "openscad_batbox";
BATTERY_BOX_SUPPORTS_HEIGHT = BATTERY_BOX_HEIGHT - BASE_THICKNESS;
BATTERY_BOX_SUPPORTS_LAYER = "openscad_batbox_supports";
BATTERY_BOX_SCREW_POS = [23.5, 17, 0];
SCREW_DEEP = 5;
MOTORS_SUPPORTS_HEIGHT = 4.5;
MOTORS_SUPPORTS_LAYER = "openscad_motors_supports";

// Generates the base
module base() {
	linear_extrude(height = BASE_THICKNESS) {
		import(file = DXF_FILE, layer = BASE_LAYER, $fn=FN);
	}
}

// Generates the supports
module supports() {
	linear_extrude(height = SUPPORTS_HEIGHT) {
		import(file = DXF_FILE, layer = SUPPORTS_LAYER, $fn=FN);
	}
}

// Generates the battery box
module battery_box() {
	difference() {
		union() {
			// The outer contour
			linear_extrude(height = BATTERY_BOX_HEIGHT) {
				import(file = DXF_FILE, layer = BATTERY_BOX_LAYER, $fn=FN);
			}
			// The supports for the cover
			linear_extrude(height = BATTERY_BOX_SUPPORTS_HEIGHT) {
				import(file = DXF_FILE, layer = BATTERY_BOX_SUPPORTS_LAYER, $fn=FN);
			}
		}
		// Substract the screws holes
		for (x = [BATTERY_BOX_SCREW_POS, -BATTERY_BOX_SCREW_POS]) {
			translate(x) {
				translate([0, 0, BATTERY_BOX_SUPPORTS_HEIGHT - SCREW_DEEP]) {
					cylinder(SCREW_DEEP + 1, SCREW_RADIUS, SCREW_RADIUS, $fn=FN);
				}
			}
		}
	}
}

// Generates the motors supports
module motors_supports() {
	linear_extrude(height = MOTORS_SUPPORTS_HEIGHT) {
		import(file = DXF_FILE, layer = MOTORS_SUPPORTS_LAYER, $fn=FN);
	}
}

mirror([1, 0, 0]) {
	union() {
		base();
		supports();
		battery_box();
		motors_supports();
	}
}
