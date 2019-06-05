function [vertexes, colors, faces] = readSTLFileMapping(fileName)
if nargin == 0 
    fileName = 'demo.stl';
end
[v, c, f] = readSTLFile(fileName);
vertexes = v';
colors = c';
faces = f';
end

