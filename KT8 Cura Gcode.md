#KT8 Dual+ Cura 15.04.6 Instellingen
Gebruik de onderstaande gcode in 'Start/End-GCode' tab van Cura 15.04.6.

#####start.gcode
```Assembly
G21
G90
M107
G28
G1 X162 F6500
G4 P800
M42 P11 S255
G4 P400
;G29
G1 Z15.0 F{travel_speed}
T1
M117 PRIMING NOZZLES
G92 E0
G1 F200 E30
G92 E0
G1 F200 E-{retraction_dual_amount}
T0
G92 E0
G1 F200 E30
G92 E0
G1 F{travel_speed}
M117 HEATING CHAMBER
;CHAMBERTEMP
;OPWARMDWELL
;SPEED1730
;SPEEDE3D
M117 KT8 DUAL+ printing
;STARTTOOL
```

#####end.gcode
```Assembly
M104 T0 S0
M104 T1 S0
M117 PRINT KLAAR
M140 S0
M42 P57 S0 ;fan 1730 off
M42 P58 S0 ;fan e3d off
M42 P5 S0 ;heated chamber off
G91
G1 E-1 F300
G1 Z+0.5 E-5 X-20 Y-20 F{travel_speed}
G28 X0 Y0
M84
G90
;{profile_string}
```

#####preSwitchExtruder.gcode
```Assembly
G91
G1 Z-10
G90
```

#####postSwitchExtruder.gcode
```Assembly
;afterTn
G91
G1 Z+10
G90
```

#####start2.gcode
```Assembly
G21
G90
M107
G28
G1 X162 F6500
G4 P800
M42 P11 S255
G4 P400
G29
G1 Z15.0 F{travel_speed}
T1
M117 PRIMING NOZZLES
G92 E0
G1 F200 E30
G92 E0
G1 F200 E-{retraction_dual_amount}
T0
G92 E0
G1 F200 E30
G92 E0
G1 F{travel_speed}
M117 HEATING CHAMBER
;CHAMBERTEMP
;OPWARMDWELL
;SPEED1730
;SPEEDE3D
M117 KT8 DUAL+ printing
;STARTTOOL
```

#####end2.gcode
```Assembly
M104 T0 S0
M104 T1 S0
M117 PRINT KLAAR
M140 S0
M42 P57 S0 ;fan 1730 off
M42 P58 S0 ;fan e3d off
M42 P5 S0 ;heated chamber off
G91
G1 E-1 F300
G1 Z+0.5 E-5 X-20 Y-20 F{travel_speed}
G28 X0 Y0
M84
G90
;{profile_string}
```
