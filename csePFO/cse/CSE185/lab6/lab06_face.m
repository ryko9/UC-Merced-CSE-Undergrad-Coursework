% David Wang CSE 185 Spring 2020 %

%lab06_face

load('att_face.mat');

num_training = size(id_training, 1);
num_testing = size(id_testing, 1);

id_predict = zeros(size(id_testing));

scale = 2;

for i = 1:num_testing

	%% extract testing image
	img_test = face_testing(:, :, i);
	vec_test = multiscale_sobel_feature(img_test, scale);

	error = zeros(num_training, 1);
	for j = 1:num_training

		%% extract training image
		img_train = face_training(:, :, j);

		%% convert training image to feature vector
		vec_train = multiscale_sobel_feature(img_train, scale);

		%% computer the square error between feature vectors
		diff = vec_train - vec_test;
		error(j) = sum(diff.^2);

	end

	%% find the image id with minimal error

	[~, min_id] = min(error);
	id_predict(i) = min_id;

end

%% compute accuracy

accuracy = sum(id_testing == id_predict)/num_testing;
fprintf('Accuracy = %f\n', accuracy);

% Using gradient magnitude as features:
%---------------------------------------%
% Scale | Accuracy
%---------------------------------------%
% 1 | 0.5313
%---------------------------------------%
% 2 | 0.550000
%---------------------------------------%
% 3 | 0.593750
%---------------------------------------%
%
% Using gradient orientation as features:
%---------------------------------------%
% Scale | Accuracy
%---------------------------------------%
% 1 | 0.5500
%---------------------------------------%
% 2 | 0.593750
%---------------------------------------%
% 3 | 0.606250
%---------------------------------------%