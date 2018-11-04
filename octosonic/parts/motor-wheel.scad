
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/wheel.dxf");
WHEEL_THICKNESS = 5;
WHEEL_LAYER = "openscad_wheel";
SUBSTRACTION_LAYER = "openscad_substract";

difference() {
	linear_extrude(height = WHEEL_THICKNESS) {
		import(file = DXF_FILE, layer = WHEEL_LAYER, $fn=FN);
	}
	translate([0, 0, 1]) {
		linear_extrude(height = WHEEL_THICKNESS - 2) {
			import(file = DXF_FILE, layer = SUBSTRACTION_LAYER, $fn=FN);
		}
	}
}