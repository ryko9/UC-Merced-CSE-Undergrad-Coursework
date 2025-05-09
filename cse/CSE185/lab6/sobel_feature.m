% David Wang CSE 185 Spring 2020 %

function [magnitude, orientation] = sobel_feature(img);

	Hy = [1, 2, 1; 0, 0, 0; -1, -2, -1]; % horizontal edge
	Hx = [1, 0, -1; 2, 0, -2; 1, 0, -1]; % vertical edge

	%% Sobel filtering

	y = imfilter(img, Hy);
	x = imfilter(img, Hx);

	%% computer gradient magnitude and orientation

	magnitude = sqrt(y.^2 + x.^2);
	orientation = atan2(y, x);

end