#!/usr/bin/env python3

import sys, os, subprocess

basedir=os.path.realpath(os.path.dirname(__file__))

argv=sys.argv
argc=len(argv)
count=argc

if argc != 2:
    exit(1)

appname=""

while count > 1:
    count-=1
    appname=argv[count]
    break

exepath=os.path.join(basedir, appname)
logpath=exepath + ".log"
outpath=exepath + ".supp"

# ~ cmd = ["valgrind", 
       # ~ "--leak-check=full",
       # ~ "--show-reachable=yes",
       # ~ "--error-limit=no",
       # ~ "--suppressions=/usr/share/glib-2.0/valgrind/glib.supp"
       # ~ "--suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp"
       # ~ "--gen-suppressions=all",
       # ~ "--log-file=" + logpath,
       # ~ exepath,
# ~ ]

cmd = ["valgrind", 
       "--leak-check=full",
       "--error-limit=no",
       "--num-callers=20",
       "--suppressions=/usr/share/glib-2.0/valgrind/glib.supp",
       "--suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp",
       "--gen-suppressions=all",
       "--log-file=" + logpath,
       exepath,
]

print(" ".join(cmd))
subprocess.run(cmd)

infile=open(logpath, "r")
outfile=open(outpath, "w")

for line in infile.readlines():
    if not line.startswith("=="):
        outfile.write(line)

infile.close()
outfile.close()


