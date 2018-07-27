%% Program to tune a and b in k_w_das
w_das=linspace(-3.5,3.5,71);
K0=0.5;
a=10;
b=0.4;
K_w_das=K0./(1+exp(-a.*w_das+b));
plot(w_das,K_w_das)