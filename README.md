# MoldBios
A basic bios-like firmware written in x86 assembly and C that runs in protected mode for QEMU and Pentium 2+ virtual machines

## Roadmap

### [X] Serial communication
### [X] Memory
### [X] GPU Driver 
### [X] PS/2
### [-] Storage Medium (Working on)
### [X] Boot
### [-] Custom Boot Protocol (Working on)
### [-] Enabling extended instruction sets (Working on)


## Notes
This project is based off of https://pitust.dev/biosdev/step1 and https://github.com/AtieP/LakeBIOS

## Building
First run "./prepare" to download the needed packages and then run "./build.sh" to build and run MoldBios under QEMU.
