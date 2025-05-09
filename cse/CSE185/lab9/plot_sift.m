function plot_sift(img, f, d)

    figure, imshow(img);
    
    perm = randperm(size(d,2)) ;
    sel = perm(:) ;
    h1 = vl_plotframe(f(:, sel)) ;
    h2 = vl_plotframe(f(:, sel)) ;
%     h3 = vl_plotsiftdescriptor(d(:,sel),f(:,sel)) ;
    set(h1,'color','k','linewidth',3) ;
    set(h2,'color','y','linewidth',2) ;
%     set(h3,'color','g') ;


end