function BuildSTLModelExample(fileName)
if nargin == 0 
    fileName = 'demo.stl';
end

[vertexes, colors, faces] = readSTLFileMapping(fileName);

patchs = patch('faces', faces, 'vertices', vertexes);
set(patchs, 'facec', 'flat');
set(patchs, 'FaceVertexCData', colors);
set(patchs, 'EdgeColor', [0.2980 0.6863 0.6667]);
light();
daspect([1 1 1])
view(3)
xlabel('X'),ylabel('Y'),zlabel('Z')
% rotate3d(axes, 'on');
end

