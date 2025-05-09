% David Wang CSE 185 Spring 2020 %

%Task 2: Hybrid Image

function img_merged = hybrid_image(img1, img2, ratio)

	%% split img1 and img2 into low/high frequency maps

	[low1, high1] = separate_frequency(img1, ratio);
	[low2, high2] = separate_frequency(img2, ratio);

	%% combine the low-frequency map of img1 with the high-frequency map of img2

	img_merged = low1 + high2;

end