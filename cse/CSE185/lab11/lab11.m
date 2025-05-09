load('att_face.mat');

k = 50; % number of eigenfaces

h = size(face_training, 1);
w = size(face_training, 2);
n_train = size(face_training, 3);
n_test = size(face_testing, 3);

fprintf('Compute eigenface...\n');
%% reshape face_training from h x w x num_train to (h*w) x num_train
X = reshape(face_training, h*w, n_train);

%% compute mean face
x_bar = mean(X, 2);

%% substract mean from X
X = bsxfun(@minus, X, x_bar);

%% compute covariance matrix
C = X * X';

%% singular value decomposition
[U, S, D] = svd(C);

%% select the first k column from U
U = U(:, 1:k);

%% encode face image as coefficients of eigenface
fprintf('Face reconstruction...\n');
f = face_training(:, :, 1);
imwrite(f, 'input.png');
figure(1), 
subplot(1, 2, 1); imshow(imresize(f, 4)); title('input');

f = f(:) - x_bar;
coef = U' * f;

%% reconstruct face image from coefficients
f_rec = x_bar + U * coef;
f_rec = reshape(f_rec, h, w);
subplot(1, 2, 2); imshow(imresize(f_rec, 4)); title('reconstruction');
imwrite(f_rec, sprintf('reconstruct_k%d.png', k));

%% encode all training data
fprintf('Convert training data to coef...\n');
coef_train = U' * X;

%% Face recognition with eigenface coefficients
fprintf('Testing...\n');
id_predict = zeros(size(id_testing));

for i = 1:n_test
    
    %% extract testing image
    img_test = face_testing(:, :, i);
    
    %% convert testing image to feature vector
    vec_test = img_test(:) - x_bar;
    coef_test = U' * vec_test;
    
    error = zeros(n_train, 1);
    for j = 1:n_train
        
        %% compute the square error between feature vectors
        diff = coef_train(:, j) - coef_test;
        error(j) = sum( diff .^2 );
        
    end
    
    %% find the image id with minimal error
    [~, min_id] = min(error);
    id_predict(i) = min_id;
    
end

%% compute accuracy
accuracy = sum(id_testing == id_predict)/n_test;
fprintf('Accuracy = %f\n', accuracy);


%---------------------------------------%
%---------- Fill in this table ---------%
%---------------------------------------%
%   k   |  Accuracy |  Squared error
%---------------------------------------%
%  10   |  0.675    |  0.325
%---------------------------------------%
%  20   |  0.6875   |  0.3125
%---------------------------------------%
%  30   |  0.71875  |  0.28125
%---------------------------------------%
%  40   |  0.7375   |  0.2625
%---------------------------------------%
%  50   |   0.7375  |  0.2625
%---------------------------------------%
