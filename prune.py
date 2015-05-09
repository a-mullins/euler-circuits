#!/usr/bin/env python3
# written by: Adam Mullins - adam.l.m@gmail.com
import sys

s  = sys.stdin.read()
li = s.split('\n')

for line in li:
    li.remove(line[::-1])

for line in li:
    print(line)
