% David Wang CSE 185 Spring 2020 %

function img_filtered = median_filter(im1, patch_size)

    % your code here
   img_filtered = zeros(size(im1));
   patcha = patch_size(2);
   patchb = patch_size(1);
   
   for a = 1 + patchb : size(im1, 2)- patcha
       for b = 1 + patcha: size(im1, 1)- patchb
           i = a - floor(patcha/2);
           ii = a + floor(patcha/2);
           j = b - floor(patchb/2); 
           jj = b + floor(patchb/2);
           
           patch = im1(j:jj, i:ii); 
           
           patch = patch(:);
           val = median(patch);
         
           img_filtered(b, a) = val;
       end
   end
end