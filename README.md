# ReadSTLFile
Read Ascii STL from matlab.
I used C++ mex function to read STL file so it's much faster than read by Matlab function.
---------------------------------------------------------------------------
If you want to customize C++ source:
after adjust readSTLFile.cpp file you have to mex that file again.
type on matlab terminal the follow code to build C++ file to function 
that matlab can run:
mex readSTLFile.cpp
