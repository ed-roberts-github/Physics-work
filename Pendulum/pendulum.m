clear

theta0=[0.01,0.03,0.1,1.0,2.0,3.0];
g=10
l=10;
t0=0;
tf=9*2*pi;
t = linspace(t0,tf,1000);

for i = 1:length(theta0)
    y0= [theta0(i);0];
    
    f = @(t,y)[y(2);-g/l*sin(y(1))];
        
    odeset('RelTol',1e-6);
    [t,yf] = ode45(f,t,y0)
    
    p(i) = subplot(2,3,i); 
    plot(t,yf(:,1)/y0(1));
    xlim([t0,tf]);
    ylim([-1,1]);
    
    str = strcat('\theta_0=', num2str(theta0(i)), ' rad');
    title(str);
    xlabel('2*pi*t')
    ylabel('theta/theta0')
    xticks([t0 tf]); 
    yticks([-1 0 1]);
    set(gca,'XTickLabel',{'0',strcat(num2str(tf/pi),'\pi')});
    
    max(yf(:,1)/y0(1))
end

pos = get(gcf,'position');
set(gcf,'position',[pos(1:2) 2*pos(3) 1.25*pos(4)]);
%exportgraphics(gcf,'untitled.pdf','ContentType','vector');
        
    