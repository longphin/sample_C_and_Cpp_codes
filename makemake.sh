#!/bin/bash
# Longphi Nguyen

errorMessage="usage: makemake.sh executable_name"
gpp="g++ -ansi -Wall -g -c"
mk="Makefile"

#
# =================== Checks =====================
#

# check if number of inputs is valid
if [ $# -lt 1 ]; then
   echo "Executable name required."
   echo $errorMessage
   exit 1
fi

#
# =================== Use ========================
#

# output file
exe=$1
shift

>$mk #initializes the file (clears all content if exists)
echo -n "$exe : " >> $mk

for fn in *.cpp; do
   echo -n "${fn%cpp}o " >> $mk
done

echo -e -n "\n\tg++ -ansi -Wall -g -o $exe $* " >> $mk

for fn in *.cpp; do
   echo -n "${fn%cpp}o " >> $mk
done

echo "" >> $mk

# dependencies
for fn in *.cpp; do
   echo -e -n "\n${fn%cpp}o : $fn " >> $mk

   # get dependencies
   dep=`grep -E "^#include[ ]*\".+\"" "$fn"`

   dep2=`echo -e -n "$dep" | sed 's/^#include *"\(.*\)*"/\1/g' | tr '\n' ' '`
   echo -e "$dep2" >> $mk
   echo -e "\t$gpp $fn" >> $mk
done

echo -e -n "\nclean : \n\trm -f $exe " >> $mk

for fn in *.cpp; do
   echo -n "${fn%cpp}o " >> $mk
done

echo "" >> $mk

