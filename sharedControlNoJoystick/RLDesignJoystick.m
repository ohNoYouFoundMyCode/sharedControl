clear all
close all
clc

bb = 0.254;
I = 0.762;

G = zpk([], [0, -bb/I], I);
r = rlocus(G);
figure(1)
plot(r(1,:),'-k','LineWidth',2);
hold on
plot(r(2,:),'-k','LineWidth',2);
plot(0,0,'xk', 'Markersize', 14);
plot(-bb/I,0,'xk', 'Markersize', 14);
hold off
% axis([-2.5 0.5 -1.5 1.5])

set(gca,...
    'LineWidth',1,...
    'fontname','Times New Roman',...
    'fontsize',14);
box on


%% Lead Controller Design
% desired settling time
ts = 0.3;       % settling time
zeta = 0.707;   % damping ratio
omegan = 4/zeta/ts;    % natural frequency

sigmad = zeta*omegan;               % real part of dominant poles
omegad = omegan*sqrt(1 - zeta^2);   % imag part of dominant poles

s1 = -sigmad + j*omegad;

Gs1 = evalfr(G,s1);
theta = pi - angle(Gs1);

% Try
%b = 0.75*sigmad;
b = 1.2*bb/I;
a = -real(s1) + imag(s1)/tan(angle(s1+b) - theta);
% a = 100;
K0 = abs(s1+a)/abs(Gs1)/abs(s1+b);

Lead = zpk(-b, -a, K0);
figure(2)
r = rlocus(Lead*G);
plot(r(1,:),'-k','LineWidth',2);
hold on
plot(r(2,:),'-k','LineWidth',2);
plot(r(3,:),'-k','LineWidth',2);
plot(0,0,'xk', 'Markersize', 14);
plot(-bb/I,0,'xk', 'Markersize', 14);
plot(-a,0,'xk', 'Markersize', 14);
plot(-b,0,'ok', 'Markersize', 14);
hold off
% axis([-0.35 0.05 -0.2 0.2])
% axis([-500 100 -300 300])

set(gca,...
    'LineWidth',1,...
    'fontname','Times New Roman',...
    'fontsize',14);
box on

DGs1 = evalfr(Lead*G,s1);
angle(DGs1);

T = feedback(Lead*G, 1);
figure(2)
step(T)
stepinfo(T)

t = 0:0.01:2;
u = ones(size(t));
y = lsim(T, u, t);
plot(t, y, '-k','LineWidth', 1)
hold on
plot(t, u, '--k','LineWidth', 0.5)
hold off
axis([0 2 0 1.2]);

ylabel('$y$~[m]','Interpreter','latex')
xlabel('$t$~[secs]','Interpreter','latex')

set(gca,...
    'LineWidth',1,...
    'ytick',[0:0.2:1.2],...
    'yticklabel',{'0' '0.2' '0.4' '0.6' '0.8' '1' '1.2'},...
    'xtick',[0:0.5:2],...
    'fontname','Times New Roman',...
    'fontsize',14);
box on
%     'xticklabel',{'0' '10' '20' '30' '40'},...


%% Lag Controller Design
Gs1 = evalfr(Lead*G,s1);
K1 = 1/abs(Gs1);

ess = 0.025;
Ks = 1/ess;
K = Ks/K1;

b1 = -real(s1)/150;
a1 = b1/K;

Lag = zpk(-b1,-a1,K1);

T = feedback(Lag*Lead*G, 1);
figure(3)
step(T)
stepinfo(T)

t = 0:0.01:2;
u = ones(size(t));
y = lsim(T, u, t);
plot(t, y, '-k','LineWidth', 1)
hold on
plot(t, u, '--k','LineWidth', 0.5)
hold off

ylabel('$y$~[m]','Interpreter','latex')
xlabel('$t$~[secs]','Interpreter','latex')

set(gca,...
    'LineWidth',1,...
    'ytick',[0:0.2:1.2],...
    'yticklabel',{'0' '0.2' '0.4' '0.6' '0.8' '1' '1.2'},...
    'fontname','Times New Roman',...
    'fontsize',14);
box on

load CrossTrackUSV.mat
return

