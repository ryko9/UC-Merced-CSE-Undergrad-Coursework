% David Wang CSE 185 Spring 2020

% Lab 08 

%% load input image

  name = 'hill';
% name = 'lines';
% name = 'bridge';

img = imread(sprintf('%s.png', name));

%% extract edge map

edge_map = edge(rgb2gray(img), 'canny', 0.1, 3);

%% Hough transform

[m, b] = hough_transform(edge_map);
x = 1:size(img, 2);
y = m * x + b;

subplot(2, 2, 1);
imshow(img); title('Hough Transform'); hold on;
plot(x, y, 'LineWidth', 4, 'Color', 'red');

h = gcf;

saveas(h, sprintf('%s_mb_line.png', name));

%% Hough Transform polar

[r, t] = hough_transform_polar(edge_map);
x = 1:size(img, 2);
y = -(cos(t)/sin(t)) * x + (r/sin(t));

subplot(2, 2, 3);
imshow(img); title('Hough Transform Polar'); hold on;
plot(x, y, 'LineWidth', 4, 'Color', 'blue');

h = gcf;
saveas(h, sprintf('%s_polar_line.png', name));