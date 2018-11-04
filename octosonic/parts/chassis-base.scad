
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/octosonic.dxf");
BASE_LAYER = "openscad_chassis_base";
CHASSIS_HEIGHT = 22.5;
SCREWS_LAYER = "openscad_chassis_screws";
SCREW_DEEP = 8;
SCREW_CENTER_OFFSET = 69.7562;
SCREW_POS = [
	[8.7, -31.55, 0],
	[23.9, 19.25, 0],
	[-23.9, 20.35, 0],
	[-19.2, -31.55, 0]
];
WALLS_HEIGHT = 12;
WALLS_LAYER = "openscad_chassis_walls";
ARDUINO_SUPPORTS_HEIGHT = 17;
ARDUINO_SUPPORTS_LAYER = "openscad_chassis_arduino";

module chassis_base() {
	linear_extrude(height = BASE_THICKNESS) {
		import(file = DXF_FILE, layer = BASE_LAYER, $fn=FN);
	}
}

module chassis_screws() {
	difference() {
		translate([0, 0, 1]) {
			linear_extrude(height = CHASSIS_HEIGHT - 1) {
				import(file = DXF_FILE, layer = SCREWS_LAYER, $fn=FN);
			}
		}
		union() {
			translate([0, 0, CHASSIS_HEIGHT - SCREW_DEEP]) {
				for (i = [0:7]) {
					rotate(i * 45 + 22.5, [0, 0, 1]) {
						translate([SCREW_CENTER_OFFSET, 0, 0]) {
							cylinder(SCREW_DEEP + 1, SCREW_RADIUS, SCREW_RADIUS, $fn=FN);
						}
					}
				}
				for (x = SCREW_POS) {
					translate(x) {
						cylinder(SCREW_DEEP + 1, SCREW_RADIUS, SCREW_RADIUS, $fn=FN);
					}
				}
			}
		}
	}
}

module chassis_walls() {
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

module chassis_arduino_supports() {
	linear_extrude(height = ARDUINO_SUPPORTS_HEIGHT) {
		import(file = DXF_FILE, layer = ARDUINO_SUPPORTS_LAYER, $fn=FN);
	}
}

union() {
	chassis_base();
	chassis_screws();
	chassis_walls();
	chassis_arduino_supports();
}