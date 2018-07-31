%% Setup
clc; clear all; close all;
I=0.7620;
bb=0.2540;

%% Subsection A
%Matlab
Num_A=[0 0 I];
Dem_A=[1 bb/I 0];
[A_A, B_A, C_A, D_A]=tf2ss(Num_A, Dem_A)

%Manual
b_a=[I];
a_a=[1 bb/I 0];
[r_a, p_a, k_a]=residue(b_a,a_a)

%% Subsection B
Num_B=[1619 1619*0.2667];
Dem_B=[1 26.49];
[A_B, B_B, C_B, D_B]=tf2ss(Num_B, Dem_B)

%% Subsection C
U=1.5;
Num_C=[0 0 0 U/100];
Dem_C=[1 5/4 0 0];
[A_C, B_C, C_C, D_C]=tf2ss(Num_C, Dem_C)

%% Overall System
A=[-0.3333 0 0 0 0 0;
    1 0 0 0 0 0;
    0 0.7620 -26.49 0 0 0;
    0 1233.7 -42456 -1.25 0 0;
    0 0 0 1 0 0;
    0 0 0 0 1 0;
    ];
B=[1 0 0 0 0 0]';

C=[0 2*0.7620 -42456 0 0 0.015];

D=(0);

[b,a]=ss2tf(A,B,C,D)

sys=tf(b,a)

isstable(sys)

rank(ctrb(A,B))
rank(obsv(A,C))