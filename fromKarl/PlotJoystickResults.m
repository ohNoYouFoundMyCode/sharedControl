close all

figure(1)
yyaxis left
plot(theta.Time, theta.Data*180/pi,'b','LineWidth',1);
ylabel('$\theta$~[deg]','Interpreter','latex')
xlabel('$t$~[sec]','Interpreter','latex')
hold on
yyaxis right
plot(Hand_Torque.Time, Hand_Torque.Data,'r','LineWidth',1);
ylabel('$\tau$~[N-m]','Interpreter','latex')
hold off

set(gca,...
    'LineWidth',1,...
    'fontname','Times New Roman',...
    'fontsize',14);
box on
% 
% text(25, 1.1,'--- Actual Trajectory','Interpreter','latex', 'fontname','Times New Roman','fontsize',14);
% text(25, 1.35,'-\,- Reference Trajectory','Interpreter','latex', 'fontname','Times New Roman','fontsize',14);
% 
figure(2)
plot(usat.Time,usat.Data,'k','LineWidth',1)
ylabel('$u_\mathrm{sat}$~[N-m]','Interpreter','latex')
xlabel('$t$~[sec]','Interpreter','latex')
set(gca,...
    'LineWidth',1,...
    'fontname','Times New Roman',...
    'fontsize',14);
box on
return
