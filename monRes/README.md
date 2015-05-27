# resources Monitor

Create ROOT file from text history file:

    createRootFile.cpp
    c++ -o createRootFile.exe createRootFile.cpp `root-config --cflags --glibs`
    
Directly creates an image:

    ./createRootFile.exe  dumpMachinesResHistory.txt 
        
Simple drawer:

    draw.cxx