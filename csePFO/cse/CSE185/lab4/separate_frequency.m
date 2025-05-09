% David Wang, CSE 185 Spring 2020%

% Task 1: Seperate Frequency

function [low_pass_img, high_pass_img] = separate_frequency(img, ratio)

	%% apply FFT

	frequency_map = fft2(img);

	%% shift the frequency map

	mapShift = fftshift(frequency_map);

	%% compute low-frequency map

	rect = zeros(size(img)); % mask

	[h, w, ~] = size(img); % height, width
    
    i = (w / 2);
    i1 = (h / 2);
    j = (w * ratio / 2);
    j1 = (h * ratio / 2);

	a = floor(i - j);
	a1 = floor(i + j);
	b = floor(i1 - j1);
	b1 = floor(i1 + j1);

	rect(b:b1, a:a1, :) = 1;

	%% seperate low-frequency and high-frequency maps 

	low_mapShift = mapShift .* rect;
	high_mapShift = mapShift .* (1 - rect);

	%% shift frequency maps back

	low_map = ifftshift(low_mapShift);
	high_map = ifftshift(high_mapShift);

	%% apply inverse FFT

	low_pass_img = real(ifft2(low_map));
	high_pass_img = real(ifft2(high_map));

end



