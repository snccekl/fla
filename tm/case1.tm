; the finite set of states
#Q = {q0,q1,q2,q3,q4,accept,reject1,reject2,reject3,reject4,reject5,reject6,reject7,reject8,reject9,reject10,reject11,reject12,reject13,reject14,reject15}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#G = {_,a,b,c,i,l,g,n,p,u,t,e}

; the start state
#q0 = q0

; the blank symbol
#B = _

; the set of final states
#F = {accept}

; the number of tapes
#N = 3

; the transition functions

; State q0: start state
q0 ___ ___ *** accept
q0 b__ ___ *** accept
q0 a__ _a_ rr* q1

; q1 copy all a to tape 2
q1 a__ _a_ rr* q1
q1 b__ __b r*r q2
q1 ___ ___ *** accept

; q2 copy all b to tape 3
q2 b__ __b r*r q2
q2 a__ ___ *** reject1
q2 ___ ___ lll q3

; q3 write c
q3 _ab cab rl* q3
q3 __b ___ *rl q4

; q4
q4 _ab _ab *r* q4
q4 __b __b *l* q3
q4 _a_ ___ l** accept

;reject
reject1 *__ ___ r** reject1
reject1 ___ ___ *** reject2
reject2 ___ i__ r** reject3
reject3 ___ l__ r** reject4
reject4 ___ l__ r** reject5
reject5 ___ e__ r** reject6
reject6 ___ g__ r** reject7
reject7 ___ a__ r** reject8
reject8 ___ l__ r** reject9
reject9 ___ ___ r** reject10
reject10 ___ i__ r** reject11
reject11 ___ n__ r** reject12
reject12 ___ p__ r** reject13
reject13 ___ u__ r** reject14
reject14 ___ t__ *** reject15




