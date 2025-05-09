% David Wang CSE 185 Spring 2020 %

function [corner_x, corner_y] = Harris_corner_detector(I, g1, g2, alpha, R_threshold)

	%% Gaussian kernels

	h1 = 1 + 2 * ceil(g1 * 2);
	h2 = 1 + 2 * ceil(g2 * 2);

	gaussian1 = fspecial('gaussian', h1, g1); %gaussian kernel 1
	gaussian2 = fspecial('gaussian', h2, g2); %gaussian kernel 2

	%% derivative filter

	Dx = [1, 0, -1];
	Dy = [1; 0; -1];
    
	%% Compute Ix x gradient and Iy y gradient

	Ix = imfilter(I, Dx, 'replicate');
	Iy = imfilter(I, Dy, 'replicate');
	Ix = imfilter(Ix, gaussian1, 'replicate');
	Iy = imfilter(Iy, gaussian1, 'replicate');

	%Ix = imfilter(imfilter(I, gaussian1, 'replicate'), Dx, 'replicate');
    % = imfilter(imfilter(I, gaussian1, 'replicate'), Dy, 'replicate');
    
    subplot(2, 3, 1)
    figure, imshow(Ix + 0.5);
    subplot(2, 3, 2)
    figure, imshow(Iy + 0.5);


	%% Squared

	Ix2 = Ix .* Ix;
	Iy2 = Iy .* Iy;
	Ixy = Ix .* Iy;

	%% Compute Sx2, Sy2, Sxy using previous values

	Sx2 = imfilter(Ix2, gaussian2, 'replicate');
	Sy2 = imfilter(Iy2, gaussian2, 'replicate');
	Sxy = imfilter(Ixy, gaussian2, 'replicate');

	%% Calculate corner response

	D = (Sx2 .* Sy2) - (Sxy .* Sxy);

	trace = Sx2 + Sy2;
    trace2 = trace .* trace;

	R = D - (alpha * trace2);

	subplot(2, 3, 3)
	imagesc(R); colormap jet; colorbar; axis image;

	%% Find corner map with R > R_threshold

	corner_map = R > R_threshold;

	subplot(2,3,4)
	imshow(corner_map);

	%% Find local maxima of R

	local_maxima = imregionalmax(R);

	subplot(2, 3, 5)
	imshow(local_maxima)


	%% Final corner map and corner coordinates (x, y)

	final_corner_map = corner_map & local_maxima;

	[corner_y, corner_x] = find(final_corner_map);

end

function P = inregionalmax(R)

	su = size(R, 2);
	sv = size(R, 1);

	i = floor(su/2);
	j = floor(sv/2);

	for u = 1 + su : size(R, 2) - su
		for v = 1 + sv : size(R, 1) - sv

			x = u - i;
			x1 = u + i;
			y = v - j;
			y1 = v + j;

			a = x;
			a1 = x1;
			b = y;
			b1 =  y1;

			P = R(b : b1, a : a1);

			if(R > R(su - 1, sv - 1) && ...
			   R > R(su - 1, sv) && ...
			   R > R(su - 1, sv + 1) && ...
			   R > R(su + 1, sv - 1) && ...
			   R > R(su + 1, sv) && ...
			   R > R(su + 1, sv + 1) && ...
			   R > R(su, sv - 1) && ...
			   R > R (su, sv + 1)) 

			end
		end
	end
end