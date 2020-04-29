clear
clc

v0 = [1 0 0]';

% + -
Ru = @(a) [
     cos(a)  sin(a)       0;
    -sin(a)  cos(a)       0;
          0       0       1];

% & ^
Rl = @(a) [
     cos(a)       0 -sin(a);
          0       1       0;
     sin(a)       0  cos(a)];

% \ /
Rh = @(a) [
          1       0       0;
          0  cos(a) -sin(a);
          0  sin(a)  cos(a)];

R = @(a) Ru(a(1)) * Rl(a(2)) * Rh(a(3));

vs = [v0'];
s = '^\XF^\XFX-F^//XFX&F+//XFX-F/X-/';
angs = [0 0 0];
phi = 0.5 * pi;
for ns = 1:length(s)
    switch s(ns)
        case 'F'
            vs = [vs; (R(angs) * v0)'];
        case '+'
            angs(1) = angs(1) + phi;
        case '-'
            angs(1) = angs(1) - phi;
        case '&'
            angs(2) = angs(2) + phi;
        case '^'
            angs(2) = angs(2) - phi;
        case '\'
            angs(3) = angs(3) + phi;
        case '/'
            angs(3) = angs(3) - phi;
    end
end

vst = vs';
xs = vst(1,:);
ys = vst(2,:);
zs = vst(3,:);
plot3(xs, ys, zs)
rotate3d