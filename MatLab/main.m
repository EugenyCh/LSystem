clear
clc

v0 = [1 0 0];

Ru = @(a) [
     cos(a)  sin(a)       0;
    -sin(a)  cos(a)       0;
          0       0       1];

Rl = @(a) [
     cos(a)       0 -sin(a);
          0       1       0;
     sin(a)       0  cos(a)];

Rh = @(a) [
          1       0       0;
          0  cos(a) -sin(a);
          0  sin(a)  cos(a)];

% xs = [0 0];
% ys = [0 1];
% zs = [0 1];
% plot3(xs, ys, zs)
% rotate3d