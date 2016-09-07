Macro
====

    root -l guiControl.cxx

    
Compile
====

    rootcling -f MyMainFrame_dict.cxx -rmf al.rootmap  MyMainFrame.h LinkDef.h

    rootcling -f MyMainFrame_dict.cxx -c  MyMainFrame.h LinkDef.h

    
    
    c++   -o guiControl.exe MyMainFrame_dict.cxx guiControl.cpp   `root-config --cflags --glibs`

    c++   -o guiControl.exe  guiControl.cpp   MyMainFrame.cxx    `root-config --cflags --glibs`

    c++   -o guiControl.exe  guiControl.cpp   MyMainFrame_dict.cxx    `root-config --cflags --glibs`

    rootcint -f guiControl.cpp -c -p -I.

    c++ -o guiControl.exe guiControl.cpp `root-config --cflags --glibs`
    
    ./guiControl.exe
    
    