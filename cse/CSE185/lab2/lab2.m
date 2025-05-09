% David Wang CSE 185 Spring 2020 %


% 1
im1 = imread('01.jpg');
frot = zeros(300, 400, 3, 'uint8'); %forward rotation

theta = 45; %degree value

a = 200;
b = 150;

cost = cosd(theta);
sint = sind(theta);


for j = 1 : 300
    
    for i = 1 : 400
        
        ii = round(cost * (i - a) + sint * (j - b) + a);
        jj = round(-sint * (i - a) + cost * (j - b) + b);

        if(ii >= 1 && ii <= 400 && jj >= 1 && jj <= 300)
            frot(jj, ii, :) = im1(j, i, :);
            
        end
    end
end

% figure, imshow(forwardRot);
imwrite(frot, 'rotate_0.jpg');

% 2
brot = zeros(300, 400, 3, 'uint8'); %backwards rotation
theta = 45;
a = 200;
b = 150;

cost = cosd(theta);
sint = sind(theta);

for j = 1 : 300
    
    for i = 1 : 400
        
        ii = round(cost * (i - a) - sint * (j - b) + a);
        jj = round(sint * (i - a) + cost * (j - b) + b);

        if(ii >= 1 && ii <= 400 && jj >= 1 && jj <= 300)
            brot(j, i, :) = im1(jj, ii, :);
            
        end
    end
end

figure, imshow(brot);
imwrite(brot, 'rotate_1.jpg');

% 3 median filter size 3
lena = im2double(imread('lena_noisy.jpg'));
patch_size3 = [3, 3];
lena3 = median_filter(lena, patch_size3);
figure, imshow(lena3);
imwrite(lena3, 'median_0.jpg');

% 4 median filter size 5
patch_size5 = [5, 5];
lena5 = median_filter(lena, patch_size5);
figure, imshow(lena5);
imwrite(lena5, 'median_1.jpg');
