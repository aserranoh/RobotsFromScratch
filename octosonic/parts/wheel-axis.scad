
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/wheel-axis.dxf");
LOW_HEIGHT = 2;
LOW_LAYER = "openscad_low";
HIGH_HEIGHT = 12;
HIGH_LAYER = "openscad_high";

linear_extrude(height = LOW_HEIGHT) {
	import(file = DXF_FILE, layer = LOW_LAYER, $fn=FN);
}

linear_extrude(height = HIGH_HEIGHT) {
	import(file = DXF_FILE, layer = HIGH_LAYER, $fn=FN);
}