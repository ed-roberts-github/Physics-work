%example: using 2D FFT in Matlab

close all;
clear all;
temp=imread('H.jpg');    % H.jpg is the image file, in my case a white "H" against a black background, created in powerpoint and exported as a jpeg
A=double(temp(:,:,1));    %choose red pixels

subplot(1,3,1)
imagesc(A);
axis square
FFTA= fft2(A); %forward transform
title('input image');

%verticle low pass filter
for i =7:540
    for j = 1:534
        FFTA(i,j)=0;
    end
end

x = 600;

%circular high pass filter
% for i = 1:543
%     for j = 1:534
%         if i^2+j^2 < x
%             FFTA(i,j) = 0;
%             FFTA(-i+544,-j+535) = 0;
%             FFTA(i,-j+535) = 0;
%             FFTA(-i+544,j) = 0;
%         end
%     end
% end


%low pass circular filter
% for i = 1:543
%     for j = 1:534
%         if i^2+j^2 > x
%             if (i<273) & (j < 273)
%                 FFTA(i,j) = 0;
%             end
%         end
%         
%          if (-i+544)^2+(-j+535)^2 > x
%              if (i>273)&(j>273)
%                  FFTA(i,j) = 0;
%              end
%          end   
%         
%         if (i)^2+(-j+535)^2 > x
%             if (i<273) & (j>273)
%                 FFTA(i,j) = 0;
%             end 
%         end
%         
%         if (-i+544)^2+(j)^2 > x
%             if (i>273)&(j<273)
%                 FFTA(i,j) = 0;
%             end
%         end
%         
%     end
% end

subplot(1,3,2)
imagesc(log(abs(fftshift(FFTA))))
axis square
title('fast fourier transform of input image with filter');

subplot(1,3,3)
AF=ifft2(FFTA);  %inverse transform
imagesc(abs(AF));
axis square
colormap hot;
title('image after filtering operation');

