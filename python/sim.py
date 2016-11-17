#!/usr/bin/env python

import sys
"[includes]"
from flame import Machine
"[includes]"

"[Parse lattice file]"
try:
    with open(sys.argv[1], "r") as F:
        mymachine = Machine(F)
except:
    #mymachine = Machine(open('./LS1FS1_latticeE.lat'))
    mymachine = Machine(open('./test.lat'))
"[Parse lattice file]"

"[Allocate State]"
thestate = mymachine.allocState({})
"[Allocate State]"

print "Initial state", thestate

"[Run simulation]"
bpms = mymachine.find(type='bpm')

#sel_cor = mymachine.find(name='LS1_CA01:DCH_D1131')[-1]
#mymachine.reconfigure(sel_cor, {'theta_x': 10})
mymachine.reconfigure(9, {'theta_x': 1.00017})
mymachine.reconfigure(10, {'theta_y': 2.00035})

r = mymachine.propagate(thestate, observe=bpms)
"[Run simulation]"

print "Final state", thestate

r01 = r[0][1]
print r01.pos
print r01.moment0_env[0]
print r01.moment0_env[2]

import numpy as np
import matplotlib.pyplot as plt

xx = np.array([(i, r[i][1].moment0_env[0]) for i in range(len(bpms))])

print(np.sum(xx[:,1]**2))

#x_c = np.loadtxt('./bld/bpm_x')

plt.plot(xx[:,0], xx[:,1], 'r-', lw=1)
#plt.plot(xx[:,0], x_c, 'b-', lw=1)
plt.show()


