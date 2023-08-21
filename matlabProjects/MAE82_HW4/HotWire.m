clear all;
close all;
clc;
% time to frequency
nspan=10000;
tspan=linspace(0,9.999,nspan);
Ts=tspan(2)-tspan(1);   %Constant dt = con stant sample frequency
Fs=1/Ts;        %spample frequency
freq=Fs*(1:nspan)/(nspan);
freq=freq.';

%read data
e040 = readcell('HotWireData.xlsx','Sheet','Step 4 0.4','Range','C27:C10026');
e100 = readcell('HotWireData.xlsx','Sheet','Step 4 1.0','Range','C27:C10026');
e161 = readcell('HotWireData.xlsx','Sheet','Step 4 1.6','Range','C27:C10026');
%format data as double
E040=cell2mat(e040);
E100=cell2mat(e100);
E161=cell2mat(e161);
%perform FFT
F040=abs(fft(E040)/nspan);
F100=abs(fft(E100)/nspan);
F161=abs(fft(E161)/nspan);

%plot
figure(1)
plot(freq,F040)
hold on
plot(freq,F100,'k')
hold on
plot(freq,F161)
hold off
xlim([1 100])   % first location is a dud
legend('0.4 in H2O','1.0 in H2O','1.61 in H2O')
xlabel('frequency (Hz)')
ylabel('|V(t)| (volts)')

%get exact frequencies
dummy=2;
for i=2:(nspan)/2
    if F040(i)>F040(dummy)
        dummy=i;
    end
end
freq040=freq(dummy)  %matlab starts plotting at f=1 not 0

dummy=2;
for i=2:(nspan)/2
    if F100(i)>F100(dummy)
        dummy=i;
    end
end
freq100=freq(dummy)  %matlab starts plotting at f=1 not 0

dummy=2;
for i=2:(nspan)/2
    if F161(i)>F161(dummy)
        dummy=i;
    end
end
freq161=freq(dummy)  %matlab starts plotting at f=1 not 0