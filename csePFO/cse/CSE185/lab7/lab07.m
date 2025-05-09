% David Wang CSE 185 Spring 2020 %

% Lab 7


%name = 'cameraman';
%name = 'checkboard';
name = 'baboon';

I = im2double(imread(sprintf('%s.png', name)));

%% given parameters from announcement

g1 = 1;
g2 = 2;
alpha = 0.04;
R_threshold = 1e-5 * 5;

%% corner detector

[corner_x, corner_y] = Harris_corner_detector(I, g1, g2, alpha, R_threshold);

%% display result

figure, imshow(I);
hold on;
plot(corner_x, corner_y, 'ro');

h = gcf; saveas(h, sprintf('%s_corners.png', name));

