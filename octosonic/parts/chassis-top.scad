
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/octosonic.dxf");
BASE_LAYER = "openscad_top_base";
WALLS_HEIGHT = 12.5;
WALLS_LAYER = "openscad_top_walls";

module chassis_top_base() {
	linear_extrude(height = BASE_THICKNESS) {
		import(file = DXF_FILE, layer = BASE_LAYER, $fn=FN);
	}
}

module chassis_top_walls() {
	difference() {
		linear_extrude(height = WALLS_HEIGHT) {
			import(file = DXF_FILE, layer = WALLS_LAYER, $fn=FN);
		}
		for (i = [0:7]) {
			rotate(45 * i, [0, 0, 1]) {
				for (x = [SENSOR_OFFSET_Y, -SENSOR_OFFSET_Y]) {
					translate([x, SENSOR_CENTER_OFFSET, WALLS_HEIGHT]) {
						rotate(90, [1, 0, 0]) {
							cylinder(BASE_THICKNESS + 2, SENSOR_RADIUS, SENSOR_RADIUS, center=true, $fn=FN);
						}
					}
				}
			}
		}
	}
}

union() {
	chassis_top_base();
	chassis_top_walls();
}