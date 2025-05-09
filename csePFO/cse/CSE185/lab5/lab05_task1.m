% David Wang CSE 185 Spring 2020 %

% Lab05 Task 1

img = im2double(imread('lena.jpg'));

sigma = 2.0;
hsize = 7;
scale = 5;

%% Gaussian Pyramid

I = img; 

gss = fspecial('gaussian', hsize, sigma);

for s = 1 : scale

	% Gaussian filter

	gf = imfilter(I, gss);

	% Save or show image

	imwrite(I, sprintf('Gaussian_scale%d.jpg', s));

	% Down-sampling

	I = imresize(gf, 1/2);

	imshow(img);

end

%% Laplacian Pyramid

I = img;

for s = 1: scale

	%% Gaussian filter

	gf = imfilter(I, gss);

	% Laplacian filtering

	lf = I - gf;

	% Save or show 

	imwrite(lf + 0.5, sprintf('Laplacian_scale%d.jpg', s)); % Change I to the output of Laplacian filter

	% Down-sampling

	I = imresize(gf, 1/2);

end
