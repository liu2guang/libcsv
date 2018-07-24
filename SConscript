import os
from building import * 

# get current dir path
cwd = GetCurrentDir()

# init src and inc vars
src = []
inc = []

# add libcsv common include
inc = inc + [cwd]

# add libcsv basic code
src = src + ['./libcsv.c']

# add group to IDE project
objs = DefineGroup('libcsv-3.0.3', src, depend = ['PKG_USING_LIBCSV'], CPPPATH = inc)

# traversal subscript
list = os.listdir(cwd)
if GetDepend('PKG_USING_LIBCSV'):
    for d in list:
        path = os.path.join(cwd, d)
        if os.path.isfile(os.path.join(path, 'SConscript')):
            objs = objs + SConscript(os.path.join(d, 'SConscript'))

Return('objs') 
