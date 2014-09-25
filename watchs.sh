#! /bin/bash
ps -A -o uid,pid,ppid,pgid,sid,comm | awk '$1=="500" && $6!="ssh" && $6!="sshd" '
