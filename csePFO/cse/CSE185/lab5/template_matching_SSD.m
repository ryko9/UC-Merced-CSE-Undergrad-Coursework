% David Wang CSE 185 Spring 2020 %

% Template Matching SSD

function [output, match] = template_matching_SSD(img, template, threshhold)

	output = img;

	su = size(template, 2);
	sv = size(template, 1);

	i = floor(su/2);
	j = floor(sv/2);

	for u = 1 + su : size(img, 2) - su
		for v = 1 + sv : size(img, 1) - sv

			x = u - i;
			x1 = u + i;
			y = v - j;
			v1 = v + j;

			a = x;
			a1 = x1;
			b = y;
			b1 =  y1;

			patch = img(b : b1, a : a1);
			patch = (patch - template).^2;

			val = sum(patch);
			val = sum(value);
			output (v, u) = val;

		end	
	end

	match = (output < threshold);

end