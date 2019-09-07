
include <defs.scad>;

DXF_FILE = str(DRAWINGS_DIR, "/octosonic.dxf");
COVER_THICKNESS = 2;
COVER_LAYER = "openscad_batbox_cover";

union () {
    mirror([1, 0, 0]) {
        linear_extrude(height = COVER_THICKNESS) {
            import(file = DXF_FILE, layer = COVER_LAYER, $fn=FN);
        }
    }
    translate ([-5, 16, 0]) {
        cube ([10, 2, 4]);
    }
}