% David Wang CSE185 Spring 2020

% Lab 09

run('vlfeat-0.9.20-bin/toolbox/vl_setup');

im1 = im2single(imread('prtn13.jpg')); % Reversing order to 12 13 makes the image look different from expected result in instructions
im2 = im2single(imread('prtn12.jpg'));

%% SIFT feature extraction

I1 = rgb2gray(im1);
I2 = rgb2gray(im2);

[f1, d1] = vl_sift(I1);
[f2, d2] = vl_sift(I2);

d1 = double(d1);
d2 = double(d2);

plot_sift(im1, f1, d1);
plot_sift(im2, f2, d2);

%% feature matching

[matches, scores] = vl_ubcmatch(d1, d2);
plot_match(im1, im2, f1, f2, matches);

%% RANSAC

e = 0.2;
s = 2;
p = 0.999;
d = 5; % delta

btx = 0; % best tx
bty = 0; % best ty

for i = 1 : 4

	p1 = f1(1:2, matches(1, i));
	p2 = f2(1:2, matches(2, i));

	tx_0 = p1(1) - p2(1);
	ty_0 = p1(2) - p2(2);

	inlier = 0;
	maxi = 0; %maxinlier

	for k = 2 : size(matches, 2)

		p1 = f1(1:2, matches(1, k));
		p2 = f2(1:2, matches(2, k));

		tx = p1(1) - p2(1);
		ty = p1(2) - p2(2);

		if(tx - tx_0) * (tx - tx_0) + (ty - ty_0) * (ty - ty_0) < d

			inlier = inlier + 1;

		end

	end

	if (inlier > maxi)

		btx = tx_0; % best tx
		bty = ty_0; % best ty

	end

end

%% Stitching

tx = round(btx);
ty = round(bty);

H = size(im1, 1);
W = size(im1, 2);

output = zeros(H + ty, W + tx, 3);
output(1:H, 1:W, :) = im1;

for y2 = 1:size(im2, 1)
	for x2 = 1:size(im2, 2)

		y1 = y2 + ty;
		x1 = x2 + tx;

		if( y1 >= 1 && y1 <= H + ty && x1 >= 1 && x1 <= W + tx )
			output(y1, x1, :) = im2(y2, x2, :);
		end

	end

end

figure, imshow(output);
imwrite(output, 'result.jpg');