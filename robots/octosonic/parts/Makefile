
OSCAD = openscad

all: base.stl battery-cover.stl chassis-base.stl chassis-top.stl motor-holder.stl motor-wheel.stl separator.stl wheel.stl wheel-axis.stl wheel-support.stl

%.stl: %.scad defs.scad
	$(OSCAD) -o $@ $<

base.stl battery-cover.stl chassis-base.stl chassis-top.stl: octosonic.dxf
motor-holder.stl: motor-holder.dxf
motor-wheel.stl: wheel.dxf
separator.stl: separator.dxf
wheel.stl: caster-wheel.dxf
wheel-axis.stl: wheel-axis.dxf
wheel-support.stl: wheel-support.dxf

.PHONY: clean
clean:
	-rm *.stl
