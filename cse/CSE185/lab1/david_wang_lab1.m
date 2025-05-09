
% David Wang CSE 185 Spring 2020
% Lab 1

%Part 1. 

im1 = imread('01.jpg'); % load the image
im1(:,:,2) = 0; % set green channel to zero

figure, imshow(im1); % show image

imwrite(im1,'green.jpg'); % write new file
fprintf('Saved green.jpg...\n');



%Part 2.

im2 = imread('01.jpg'); % load image
im2 = im2double(im2);

im2 = .299 * im2(:,:,1) + .587 * im2(:,:,2) + .114 * im2(:,:,3); % set grey scale

figure, imshow(im2); % show image

imwrite(im2,'gray.jpg'); % save image
fprintf('Saved gray.jpg...\n');




%Part 3.

im3 = imread('01.jpg');
im3 = imrotate(im3, 90); % rotate 90 degrees

figure, imshow(im3);
 
imwrite(im3,'rotate.jpg');
fprintf('Saved rotate.jpg...\n');



%Part 4

img4 = imread('01.jpg');

[m,n] = size(img4); % initializing matrix

img4 = img4(30:270,100:300, :);
imshow(img4);

imwrite(img4,'crop.jpg');
fprintf('Saved crop.jpg...\n');




%Part 5s

img5 = imread('01.jpg'); % load
img5 = flip(img5, 2); 

figure, imshow(img5); % show

imwrite(img5, 'flip.jpg'); % save
fprintf('Saved flip.jpg...\n');





%Part 6.

img1 = imread('01.jpg'); % load images 1 through 4
img2 = imread('02.jpg');
img3 = imread('03.jpg');
img4 = imread('04.jpg');

background = zeros(300 * 2 + 10, 400 * 2 + 10, 3, 'uint8'); % creating background
background(1:300,1:400,:)=img1;
background(1:300,410:809,:)=img2;
background(310:609,1:400,:)=img3;
background(310:609,410:809,:)=img4;

figure, imshow(background); % show image

imwrite(background,'combine.jpg'); % save 
fprintf('Saved combine.jpg...\n');




%Part 7

img1 = imread('05.jpg'); %change to vector
img2 = imread('06.jpg');  

img1 = img1(:);
img2 = img2(:);

avg=(img1+img2)/2; % average
avg = reshape(avg,375,1242,3);

figure, imshow(avg);

imwrite(avg,'average.jpg'); %save 
fprintf('Saved average.jpg...\n');
