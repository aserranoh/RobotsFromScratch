
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/caster-wheel.dxf");
WHEEL_HEIGHT = 6;
WHEEL_LAYER = "openscad_wheel";

linear_extrude(height = WHEEL_HEIGHT) {
	import(file = DXF_FILE, layer = WHEEL_LAYER, $fn=FN);
}