# start
00, ,<,gtf

# go to the front of input message 
gtf,0,<,gtf
gtf,1,<,gtf
gtf,2,<,gtf
gtf,3,<,gtf
gtf,4,<,gtf
gtf,5,<,gtf
gtf,6,<,gtf
gtf,7,<,gtf
gtf,8,<,gtf
gtf,9,<,gtf
gtf, ,>,r0

# RODs processing 
r0,0,>,r0
r0,1,>,r1
r0,2,>,r2
r0,3,>,r3
r0,4,>,r4
r0,5,>,r5
r0,6,>,r6
r0,7,>,r7
r0,8,>,r8
r0,9,>,r9
r0, ,>,yes

r1,0,>,r10
r1,1,>,r0
r1,2,>,r1
r1,3,>,r2
r1,4,>,r3
r1,5,>,r4
r1,6,>,r5
r1,7,>,r6
r1,8,>,r7
r1,9,>,r8
r1, ,>,no

r2,0,>,r9
r2,1,>,r10
r2,2,>,r0
r2,3,>,r1
r2,4,>,r2
r2,5,>,r3
r2,6,>,r4
r2,7,>,r5
r2,8,>,r6
r2,9,>,r7
r2, ,>,no

r3,0,>,r8
r3,1,>,r9
r3,2,>,r10
r3,3,>,r0
r3,4,>,r1
r3,5,>,r2
r3,6,>,r3
r3,7,>,r4
r3,8,>,r5
r3,9,>,r6
r3, ,>,no

r4,0,>,r7
r4,1,>,r8
r4,2,>,r9
r4,3,>,r10
r4,4,>,r0
r4,5,>,r1
r4,6,>,r2
r4,7,>,r3
r4,8,>,r4
r4,9,>,r5
r4, ,>,no

r5,0,>,r6
r5,1,>,r7
r5,2,>,r8
r5,3,>,r9
r5,4,>,r10
r5,5,>,r0
r5,6,>,r1
r5,7,>,r2
r5,8,>,r3
r5,9,>,r4
r5, ,>,no

r6,0,>,r5
r6,1,>,r6
r6,2,>,r7
r6,3,>,r8
r6,4,>,r9
r6,5,>,r10
r6,6,>,r0
r6,7,>,r1
r6,8,>,r2
r6,9,>,r3
r6, ,>,no

r7,0,>,r4
r7,1,>,r5
r7,2,>,r6
r7,3,>,r7
r7,4,>,r8
r7,5,>,r9
r7,6,>,r10
r7,7,>,r0
r7,8,>,r1
r7,9,>,r2
r7, ,>,no

r8,0,>,r3
r8,1,>,r4
r8,2,>,r5
r8,3,>,r6
r8,4,>,r7
r8,5,>,r8
r8,6,>,r9
r8,7,>,r10
r8,8,>,r0
r8,9,>,r1
r8, ,>,no

r9,0,>,r2
r9,1,>,r3
r9,2,>,r4
r9,3,>,r5
r9,4,>,r6
r9,5,>,r7
r9,6,>,r8
r9,7,>,r9
r9,8,>,r10
r9,9,>,r0
r9, ,>,no

r10,0,>,r1
r10,1,>,r2
r10,2,>,r3
r10,3,>,r4
r10,4,>,r5
r10,5,>,r6
r10,6,>,r7
r10,7,>,r8
r10,8,>,r9
r10,9,>,r10
r10, ,>,no

# print answer message
yes, ,1,hlt
no, ,0,hlt

# halt (end of work)
hlt,0,>,hlt
hlt,1,>,hlt
hlt, ,#,hlt
