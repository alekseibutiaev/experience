#!/bin/bash

echo "#"
echo "# 74XX${1}x"
echo "#"
echo "DEF 74XX${1}x U 0 40 Y Y 1 F N"
echo "F0 \"U\" 0 100 50 H V C CNN"
echo "F1 \"74XX${1}x\" 0 -100 50 H V C CNN"
echo "F2 \"\" 0 0 50 H I C CNN"
echo "F3 \"\" 0 0 50 H I C CNN"
echo "DRAW"
echo "X GND ~ 300 -300 0 L 50 50 0 1 W N"
echo "X VCC ~ 300 300 0 L 50 50 0 1 W N"
echo "ENDDRAW"
echo "ENDDEF"

