#!/bin/sh

PARENTDIR=$(pwd)
EXAMPLEDIR=$PARENTDIR'/example'
LOGFILE='test.log'
FILE1=$EXAMPLEDIR'/mountdir/file1.txt'
FILE2=$EXAMPLEDIR'/mountdir/file2.txt'
CPF1=$EXAMPLEDIR'/mountdir/file1_copy.txt'
CPF2=$EXAMPLEDIR'/mountdir/file2_copy.txt'

echo '\n\n-----------------------------RUNNING TEST SCRIPT!-----------------------------\n\n'
echo '\n### STAGE 1 ###\n'
bash -c './run.sh 1'
echo '\nSwitching from $PARENTDIR to mount directory...\n'
cd $EXAMPLEDIR
echo '\nCreating logfile\n'
bash -c '> $LOGFILE'
ls -lR >> $LOGFILE && echo '\n\n' >> $LOGFILE
echo '\nWriting file data to first file\n' && echo '\nWriting file data to first file\n' >> $LOGFILE
sleep 1
bash -c 'gedit '$FILE1
echo '\nWriting similar (but not equal) data to second file with cat\n' &&  echo '\nWriting similar (but not equal) data to second file\n' >> $LOGFILE
sleep 1
bash -c  'gedit '$FILE2
ls -lR >> $LOGFILE && echo '\n\n' >> $LOGFILE
echo '\n### STAGE 2 ###\n'
echo '\nCreating copy files\n' && echo '\nCreating copy files\n' >> $LOGFILE
sleep 1
cp $FILE1 $CPF1 && cp $FILE2 $CPF2
ls -lR >> $LOGFILE && echo '\n\n' >> $LOGFILE
echo '\n### STAGE 3 ###\n'
echo '\nUnmounting system...\n'
sleep 1
cd ..
bash -c './run.sh 2'
echo '\n\n-----------------------------EXITING TEST SCRIPT!-----------------------------\n\n'