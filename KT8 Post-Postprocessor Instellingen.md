#KT8 Post-Postprocessor Instellingen
Gebruik de onderstaande gcode in de KT8 Post-Postprocessor applicatie.

Start Tool Gcode T0/T1:
```Assembly
T0
G1 X-67 F6500 ; go to right parking lot
G4 P250 ;dwell 250ms
M42 P6 S2 ; electro magnet T0 on
G4 P400 ;dwell 400ms
```

Toolswitch naar T0 (1730 Hotend)
```javascript
T0
G1 X162 F6500 ; go to left parking lot
G4 P250 ;dwell 250ms
M42 P11 S255 ; electro magnet 2 off
G4 P400 ;dwell 400ms
G1 X-67 F6500 ; go to right parking lot
G4 P250 ;dwell 250ms
M42 P6 S2 ; electro magnet 1 on
G4 P400 ;dwell 400ms
```

Toolswitch naar T1 (E3D Hotend)
```javascript
G1 X-67 F6500 ; go to right parking lot
G4 P250 ;dwell 250ms
M42 P6 S255 ; electro magnet 1 off
G4 P400 ;dwell 400ms
G1 X162  F6500 ; go to left parking lot
G4 P250 ;dwell 250ms
M42 P11 S2 ; electro magnet 2 on
G4 P400 ;dwell 400ms
T1
```
