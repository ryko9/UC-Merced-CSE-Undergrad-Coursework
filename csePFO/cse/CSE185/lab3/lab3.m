%Andrew Nguyen
img = im2double(imread('lena.jpg'));

V = [1, 0, -1; 2, 0 ,-2; 1, 0, -1];
H = [1, 2, 1; 0, 0, 0; -1, -2, -1];

% Number 1
img_sobelH = sobel_filter(img, H);
imwrite(img_sobelH, 'sobel_y.jpg');

% Number 2
img_sobelV = sobel_filter(img, V);
imwrite(img_sobelV, 'sobel_x.jpg');

% Number 5
sigma5 = 2;
hsize5 = 5;

gaussian5 = gaussian_filter(img, hsize5, sigma5);
imwrite(gaussian5, 'gaussian_5.jpg');

% Number 6
sigma9 = 4;
hsize9 = 9;

gaussian9 = gaussian_filter(img, hsize9, sigma9);
imwrite(igaussian9, 'gaussian_9.jpg');