clear all
clc

% DO NOT CHANGE THIS VALUES
a = 90.0;
xT = 0;
yT = 0;
zT = 0;
hT = [1 0 0];
lT = [0 1 0];
uT = [0 0 1];
a = a/180*pi ; % deg -> rad
length_F = 1;

% THESE MATRICES MUSTN'T BE CHANGED AS WELL
% rotation matrix R_U(a) 
Rum = [ cos(a)   sin(a)  0; ...
        -sin(a)  cos(a)  0; ...
        0        0       1];
       
Rup = [ cos(-a)   sin(-a)  0; ...
        -sin(-a)  cos(-a)  0; ...
        0         0        1];
       
% rotation matrix R_L(a) 
Rlp = [ cos(a)  0  -sin(a); ...
        0       1  0; ...
        sin(a)  0  cos(a)];
 
Rlm = [ cos(-a)  0  -sin(-a); ...
        0        1  0; ...
        sin(-a)  0  cos(-a)];
 
% rotation matrix R_H(-a)
Rhp = [ 1  0       0; ...   
        0  cos(a)  -sin(a); ...
        0  sin(a)  cos(a)];

Rhm = [ 1  0        0; ...   
        0  cos(-a)  -sin(-a); ...
        0  sin(-a)  cos(-a)];

% rotation matrix R_H(180)
Rbk = [ -1  0   0; ...
        0   -1  0; ...
        0   0   1];

%axiom = '^\F^\F-F^//F&F+//F-F/-/';
axiom = '^\^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/F^\^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/-F^//^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/&F+//^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/-F/^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F^//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/&F+//^\XF^\XFX-F^//XFX&F+//XFX-F/X-/F^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-F/^\XF^\XFX-F^//XFX&F+//XFX-F/X-/-/-/';

figure(1)
hold on
for i = 1:length(axiom)
    cmdT = axiom(i);
    switch cmdT
    case 'F'
        % how to plot a 'F' line
        newxT = xT + length_F*hT(1);
        newyT = yT + length_F*lT(1);
        newzT = zT + length_F*uT(1);
        line([xT newxT],[yT newyT],[zT newzT]);
        xT = newxT;
        yT = newyT;
        zT = newzT;
    case '+'
        % rotate anticlockwise
        hT = hT * Rup;
        lT = lT * Rup;
        uT = uT * Rup;
    case '-'
        % rotate clockwise
        hT = hT * Rum;
        lT = lT * Rum;
        uT = uT * Rum;
    case '&'
        % grade downwards
        hT = hT * Rlp;
        lT = lT * Rlp;
        uT = uT * Rlp;
    case '^'
        % grade upwards
        hT = hT * Rlm;
        lT = lT * Rlm;
        uT = uT * Rlm;
    case '\'
        % roll anticlockwise
        hT = hT * Rhp;
        lT = lT * Rhp;
        uT = uT * Rhp;
    case '/'
        % roll clockwise
        hT = hT * Rhm;
        lT = lT * Rhm;
        uT = uT * Rhm;
    case '|'
        % turn around
        hT = hT * Rbk;
        lT = lT * Rbk;
        uT = uT * Rbk;
    end
end
rotate3d on;