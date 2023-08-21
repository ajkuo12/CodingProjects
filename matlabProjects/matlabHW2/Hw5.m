%%Part B
fs = 14;
fn = 'Arial';
lw = 2;
primColor = [39 116 174]/255;
secColor  = [255 209 0]/255;

t_range = [0 1];
y_0 = [0 10];
stepSize = 0.001;
stepSizeReduced = 0.0001;

[t,y] = RK4solver(@(t,y)exoBootsODEfun1(t,y)...
    ,t_range, y_0, stepSize);
[th,yh] = RK4solver(@(t,y)exoBootsODEfun1(t,y)...
    ,t_range, y_0, stepSizeReduced);
                        
figure(1);
plot(y(2,:),y(1,:),'linewidth',lw, 'color', primColor);
xlabel('Angular Velocity in (rad/s)')
ylabel('Current in (A)')
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')

figure(2);
plot(yh(2,:),yh(1,:),'linewidth',lw, 'color', primColor);
xlabel('Angular Velocity in (rad/s)')
ylabel('Current in (A)')
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')

figure(3)
subplot(2,1,1)
plot(th,yh(2,:),'color',secColor,'linewidth',lw)
title('Angular Velocity vs Time')
xlabel('Time in (s)')
ylabel('Angular Velocity in (rad/s)')
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')
subplot(2,1,2)
plot(th,yh(1,:),'color',primColor,'linewidth',lw)
xlim([0 1]);
title('Current vs Time')
xlabel('Time in (s)')
ylabel('Current in (A)')
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')

%%
exo = load('ExoBootOutput.mat');
exoTime = exo.exoTime;
exoTorque = exo.exoTorque;
exoAngle = deg2rad(exo.exoAngle);
y_00 = [0 0 0];
t_range2 = [0 0.75];

stepSize3 = 0.0001;
N =1;

[t_y,y_1] = RK4solver(@(t,y) exoBootsNHODEfun(t,y,exoTime,exoTorque,exoAngle, N),...
       t_range2, y_00, stepSize3);
figure(5)
subplot(3,1,1)
plot(t_y,y_1(1,:),'color',secColor,'linewidth',lw)
xlabel('Time in (s)')
ylabel('Current in (A)','FontSize',4)
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')
subplot(3,1,2)
plot(t_y,y_1(2,:),'color',primColor,'linewidth',lw)
xlabel('Time in (s)')
ylabel('Angular Velocity in (rad/s)')
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')
subplot(3,1,3)
plot(t_y,y_1(3,:),'color','k','linewidth',lw)
xlabel('Time in (s)')
ylabel('Output Angle in (rad)')
set(gca,'FontSize',fs,'FontName',fn,'linewidth',lw,'box','off')