% David Wang CSE 185 Spring 2020 %

% Template Matching with NormCom

function [output, match] = template_matching_SSD(img, template, threshhold)

	output = img;

	su = size(template, 2);
	sv = size(template, 1);

	i = floor(su/2);
	j = floor(sv/2);

	for u = 1 + su : size(img, 2) - su
		for v = 1 + sv : size(img, 1) - sv

			a = u - i;
			a1 = u + i;
			b = v - j;
			b1 = v + j;

			x = a;
			x1 = a1;
			y = b;
			y1 =  b1;

			patch = img(y : y1, x : x1);

			% Normalized Cross-Correlation

			pat1 = patch(:);
			temp1 = template(:);

			pat1 = pat1 - mean(pat1);
			temp1 = temp1 - mean(temp1);

			pat1 = pat1 / norm(pat1);
			temp1 = temp1 / norm(temp1);

			val = dot(pat1, temp1);

			output (v, u) = val;

		end
	end

	match = (output < threshold);

end