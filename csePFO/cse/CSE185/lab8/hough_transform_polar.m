% David Wang CSE 185 Spring 2020 

% Hough Transform Polar

function [r, t] = hough_tranform_polar(edge_map)

	%% find x, y position from edge map
	[edge_y, edge_x] = find(edge_map);

	%% range of r

	H = size(edge_map, 1);
	W = size(edge_map, 2);
	r_max = round(sqrt(H^2 + W^2));
	r_min = -r_max;
	r_step = 1;
	r_range = r_min : r_step : r_max;

	%% range of theta

	t_step = 0.01;
	t_range = -pi/2 : t_step : pi/2;

	%% create vote matrix

	V = zeros(length(r_range), length(t_range));

	%% TODO: add votes

	for i = 1:length(edge_y)
		y = edge_y(i);
		x = edge_x(i);
		for t_index = 1:length(t_range)
			t = t_range(t_index);

			r = x * cos(t) + y * sin(t);

			if(r_max >= r && r_min <= r)
				r_index = round((r-r_min)/r_step) + 1;
				V(r_index, t_index) = V(r_index, t_index) + 1;
			end

		end

	end

	%% visualize votes

	subplot(2,2,4);
    imagesc(V); xlabel('theta'); ylabel('r');   

	%% find the maximal vote
	max_vote = max(V(:));
	[max_r_index, max_t_index] = find(V == max_vote );
	r = r_range(max_r_index);
	t = t_range(max_t_index);

end