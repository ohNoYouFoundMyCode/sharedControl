%B_residue=[1.5/100];
%A_residue=[0 5/4 0 0];
%[r, p, k]=residue(B_residue,A_residue)

A=[-0.333 0 0 0 0;
    0 0 0 0 0;
    -42456 -42456 -26.49 0 0;
    1619 1619 0 0 0;
    0 0 0.12 0.12 0]

B=[-2.286 2.286 0 0 0]'

rank(ctrb(a,b))
