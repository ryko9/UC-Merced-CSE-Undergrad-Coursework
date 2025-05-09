% David Wang CSE 185 Spring 2020 %

%img_dir = 'data/Army';
%img_dir = 'data/Dumptruck';
%img_dir = 'data/Backyard';
img_dir = 'data/Basketball';

im1 = im2double(imread(fullfile(img_dir, 'frame10.png')));
im2 = im2double(imread(fullfile(img_dir, 'frame11.png')));

%% paramters
%windows_size = 45;

window_size = 45;
k = 4; % number of iterations

w = floor(window_size/2);
s = w + 10;

%% convert to gray-scale
I1 = rgb2gray(im1);
I2 = rgb2gray(im2);

%% compute gradients

Ix_m = imfilter(I1, [1 -1; 1 -1], 'replicate');
Iy_m = imfilter(I1, [1 1; -1 -1], 'replicate');

%% computer optical flow

u = zeros(size(I1));
v = zeros(size(I1));

u_next = zeros(size(I1));
v_next = zeros(size(I1));

for t = 1:k
	for i = 1 + s: size(Ix_m, 1) - s
		for j = 1 + s : size(Ix_m, 2) - s

			%% extract Ix, Iy, It

			Ix = Ix_m(i-w : i+w, j-w : j+w);
			Iy = Iy_m(i-w : i+w, j-w : j+w);

			i2 = round(i + v(i, j));
			j2 = round(j + u(i, j));

			It = I1(i-w : i+w, j-w : j+w) - I2(i2 - w : i2 + w, j2 - w : j2 + w);

			%% convert Ix, Iy, It to vectors

			Ix = Ix(:);
			Iy = Iy(:);
			It = It(:);

			%% construct matrix A and vector b

			A = [Ix, Iy];
			b = -It;

			%% solve A x = b 

			x = A \ b;

			u_next(i,j) = x(1);
			v_next(i,j) = x(2);

		end

	end

	u = u + u_next;
	v = v + v_next;

end

plot_flow(im2, u, v);
h = gcf;
saveas(h, 'result_basketball_windowsize45.png');