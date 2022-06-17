echo off

path = %path%;C:\BC_3\utils\gnumake382-w32
path = %path%;C:\Keil_v5\ARM\ARMCC\BIN

echo on
gnumake382-w32 -f carmen_controller.mk

