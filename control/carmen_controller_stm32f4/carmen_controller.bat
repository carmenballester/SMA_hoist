echo off

path = %path%;C:\Users\carme\Documents\RoboticsLab\Research\lib_root\BC_3\utils\gnumake382-w32
path = %path%;C:\Users\carme\Documents\RoboticsLab\Research\lib_root\KeilV5\ARM\ARMCC\BIN

echo on
gnumake382-w32 -f carmen_controller.mk

