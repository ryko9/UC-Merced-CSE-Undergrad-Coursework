% David Wang CSE 185 Spring 2020 %

% Lab 04: Frequency Domain Operation

img = im2double(imread('lena.jpg'));

rt = 0.1; % ratio = 0.1

[lowPass, highPass] = separate_frequency(img, rt); %low pass and high pass image

mari = im2double(imread('marilyn.jpg')); % Marilyn
ein = im2double(imread('einstein.jpg')); % Einstein

figure, imshow(lowPass)
figure, imshow(highPass + 0.5)

imwrite(lowPass, 'lena_low_0.1.jpg'); % Task 2
imwrite(highPass + 0.5, 'lena_high_0.1.jpg');

rt = 0.2; % ratio = 0.2

[lowPass, highPass] = separate_frequency(img, rt);

figure, imshow(lowPass)
figure, imshow(highPass + 0.5)

imwrite(lowPass, 'lena_low_0.2.jpg'); % Task 3
imwrite(highPass + 0.5, 'lena_high_0.2.jpg');

% Task 5-6

rt = 0.05; 

hybridImg = hybrid_image(mari, ein, rt);

figure, imshow(hybridImg);
imwrite(hybridImg, 'hybrid_1.jpg');

hybridImg1 = hybrid_image(ein, mari, rt);

figure, imshow(hybridImg1);
imwrite(hybridImg1, 'hybrid_2.jpg');

% Task 8 

%img = im2double(imread('new_york.jpg'));
%frequency_map = fftshift(fft2(img));
%figure, imagesc(log(abs(frequency_map) + 1)), colormap jet;

%img = im2double(imread('flowers.jpg'));
%frequency_map = fftshift(fft2(img));
%figure, imagesc(log(abs(frequency_map) + 1)), colormap jet;

img = 'new_york.jpg';
vimg = im2double(imread(img));
visualization(vimg);








