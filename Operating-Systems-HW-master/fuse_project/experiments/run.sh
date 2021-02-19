#!/bin/sh

### This is a subscript called in test.sh main script. It compiles src files, runs bbfs and unmounts filesystem

FIRST_ARG=$1
EXPERIMENT_DIR="experiments"
EXAMPLE_DIR="example"
SRCDIR="../filesystem/src"

# make
# cd example
# ../../filesystem/src/bbfs rootdir mountdir
if [ "$FIRST_ARG" -eq "1" ] ; then
	cd $EXAMPLE_DIR
	bash -c '> bbfs.log'	
	cd ../
	cd $SRCDIR
	bash -c 'make all'
	cd ../../$EXPERIMENT_DIR/$EXAMPLE_DIR
	mkdir -p mountdir
	mkdir -p rootdir
	EXEC_PATH="../../filesystem/src/bbfs"
	exec $EXEC_PATH rootdir/ mountdir/
#
elif [ "$FIRST_ARG" -eq "2" ] ; then
	cd $EXAMPLE_DIR
	echo $(pwd)
	fusermount -u mountdir
	cd ../$SRCDIR
	bash -c 'make clean'
	echo "Just unmounted"
fi

