% David Wang CSE 185 Spring 2020 %

% Visualization

function visualization(img)


frequency_map = fftshift(fft2(img));

figure, imagesc(log(abs(frequency_map) + 1)), colormap jet;

end