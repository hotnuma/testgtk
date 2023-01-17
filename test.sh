#!/usr/bin/bash

BASEDIR="$(dirname -- "$(readlink -f -- "$0";)")"

cmd="valgrind --show-leak-kinds=definite"
cmd+=" --suppressions=/usr/share/glib-2.0/valgrind/glib.supp"
cmd+=" --suppressions=/usr/share/gtk-3.0/valgrind/gtk.supp"
cmd+=" ${BASEDIR}/build/testgtk"

$cmd

