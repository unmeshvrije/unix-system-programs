#!/bin/sh

#
# Copy all extensions from ext_ignore.txt files to gitignore
# Go over all executable files in the directory
# Append them to gitignore
#
cat ext_ignore.txt > .gitignore && ls | while read filename; do is_executable=$(file "$filename" | grep "executable" | wc -l); if [ "$is_executable" -eq "1" ]; then echo $filename >> .gitignore; fi; done
