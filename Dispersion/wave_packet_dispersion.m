clear;
k_0 = 1;
sgm = k_0/10;
dk = sgm/10;
c = 1;
d = 0;
m_0 = 30;
km = k_0;
w = 0;
t = [0 100 200 300];
psi = [];
x = linspace(0,1000,1000);

hold on

for g=1:4
    for e =1:length(x)
        psi(e) = 0;
    end
        for i=1:length(x)
            for m = -m_0:m_0
                km = k_0 + m*dk;
                w = c*km+d*km^3;
                psi(i) = psi(i) + exp(-(km-k_0)^2/(2*sgm^2))*cos(km*x(i)-w*km*t(g));
            end      
        end
    plot(x,psi)
end


title('Wave packet d=0.2')
xlabel('x/m')
ylabel('Psi/m')
legend('t=0s','t=100s','t=200s','t=300s')
