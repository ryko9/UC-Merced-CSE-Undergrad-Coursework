% David Wang, CSE 185 Spring 2020%

% Task 1: Seperate Frequency

function [low_pass_img, high_pass_img] = separate_frequency(img, ratio)

	%% apply FFT

	frequency_map = fft2(img);

	%% shift the frequency map

	mapShift = fftshift(frequency_map);

	%% compute low-frequency map

	rect = zeros(size(img)); % mask

	i = size(img, 1);
	i1 = size(img, 2);
	j = ratio * i;
	j1 = ratio * i1;


	a = round(i/2 - j);
	a1 = round(i/2 + j);
	b = round(i1/2 - j1);
	b1 = round(i1/2 + j1);

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



