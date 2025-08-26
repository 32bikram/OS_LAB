#!/bin/bash
#Assignment 1A:

#Group-A2
#Team No-08
#Date- 26-7-2025

# Name - Partha Roy
# Roll No - 302411001004

# Name - Bikram Sarkar
# Roll No - 302411001008

# Name - Bikram Dutta
# Roll No - 002311001071





#who 
#       -It displays the information about all the users who have logged into the system currently
#	Syntax:
#		who
#	Output:
#		be2341   pts/0        2025-07-23 12:17 (172.16.4.211)
#		be23L04  pts/1        2025-07-23 13:02 (172.16.4.205)
#		be2368   pts/3        2025-07-23 13:03 (172.16.4.204)
#		be2362   pts/4        2025-07-23 12:25 (172.16.4.220)
#		be23L07  pts/6        2025-07-23 12:25 (172.16.4.215)
#		be2365   pts/7        2025-07-23 12:27 (172.16.4.227)
#		be2356   pts/8        2025-07-23 12:27 (172.16.4.209)
#		be2373   pts/9        2025-07-23 12:28 (172.16.4.221)
#		be2355   pts/10       2025-07-23 12:44 (172.16.4.216)
#		be2358   pts/12       2025-07-23 13:09 (172.16.4.203)
#		be2357   pts/13       2025-07-23 12:33 (172.16.4.212)
#		be2313   pts/14       2025-07-23 12:33 (172.16.14.45)
#		be2359   pts/15       2025-07-23 12:33 (172.16.4.213)
#		be2313   pts/16       2025-07-23 12:35 (172.16.14.45)
#		be2358   pts/18       2025-07-23 12:45 (172.16.4.203)
#		be2371   pts/19       2025-07-23 12:50 (172.16.4.202)
#		be2354   pts/20       2025-07-23 12:52 (172.16.4.201)
#		be2361   pts/21       2025-07-23 12:53 (172.16.4.214)
#		be2369   pts/23       2025-07-23 13:04 (172.16.4.207)
#		be2357   pts/24       2025-07-23 13:04 (172.16.4.212)
#		be2360   pts/25       2025-07-23 13:04 (172.16.4.218)
#		be2359   pts/27       2025-07-23 13:07 (172.16.4.213)
#		be2354   pts/28       2025-07-23 13:08 (172.16.4.201)
#		be2361   pts/30       2025-07-23 13:14 (172.16.4.214)
#		be2389   pts/31       2025-07-23 13:14 (172.16.4.226)
#		be2356   pts/32       2025-07-23 13:14 (172.16.4.209)
#		be23L04  pts/33       2025-07-23 13:14 (172.16.4.205)


#whoami
#        :- It displays Current username, Terminal number, date and time at which user logged into the system
#	Syntax:
#		$whoami
#	Output:
#		[be23L04@localhost ~]$ whoami
#		be23L04


#pwd
#:      - It displays current working directory
#	Syntax:
#		$pwd
#	Output:
#		[be23L04@localhost ~]$ pwd
#		/home/usr/student/ug/yr23/be23L04


#date
#:      - It displays system date and time
#	Syntax:
#		$date
#	Output:
#		[be23L04@localhost ~]$ date
#		Wed Jul 23 13:23:56 IST 2025


#ls 
#       - It lists the files and directories stored in the current directory. To list the files in a directory use the following 
#	Syntax: 
#		$ls dirname
#	Example:
#		$ls /usr
#	Output:
#		[be23L04@localhost ~]$ ls /usr
#		bin  etc  games  include  java  lib  lib64  libexec  local  sbin  share  src  tmp


#mkdir 
#       – It is used to create directories.
#	Syntax:
#		$mkdir dir_name
#	Example:
#		$mkdir newDir
#	Output:
#		[be23L04@localhost new]$ mkdir newDir
#		[be23L04@localhost new]$ ls
#		newDir


#clear
#       - It clears the screen
#	Syntax:
#		$clear
#	Output:
#		(Clears the screen)


#cd 
#       - It is used to change the current working directory to any other directory specified
#	Syntax:
#		$cd <path_to_the_target_directory>
#	Example:
#	 	cd /home
#	Output:
#		[be23L04@localhost new]$ pwd
#		/home/usr/student/ug/yr23/be23L04/new
#		[be23L04@localhost new]$ cd /home
#		[be23L04@localhost home]$ pwd
#		/home


# df 
#       - It displays currently mounted file systems.Total disk space, used, available, and mount point
# 	Syntax:
# 		df [options] [file...]
#   Output:
#         [be2371@localhost ~]$ df
#         Filesystem                   1K-blocks      Used  Available Use% Mounted on
#         /dev/mapper/scientific-root   52399104  27789108   24609996  54% /
#         devtmpfs                      32758584         0   32758584   0% /dev
#         tmpfs                         32774652     10340   32764312   1% /dev/shm
#         tmpfs                         32774652    788668   31985984   3% /run
#         tmpfs                         32774652         0   32774652   0% /sys/fs/cgroup
#         /dev/sda2                      1039616    238088     801528  23% /boot
#         /dev/mapper/scientific-home 2256669952 136335520 2120334432   7% /home
#         tmpfs                          6554932        16    6554916   1% /run/user/42
#         tmpfs                          6554932         0    6554932   0% /run/user/3067
#         tmpfs                          6554932         0    6554932   0% /run/user/3097
#         tmpfs                          6554932         0    6554932   0% /run/user/3014
#         tmpfs                          6554932         0    6554932   0% /run/user/3107
#         tmpfs                          6554932         0    6554932   0% /run/user/3218
#         tmpfs                          6554932         0    6554932   0% /run/user/3213
#         tmpfs                          6554932         0    6554932   0% /run/user/3271
#         tmpfs                          6554932         0    6554932   0% /run/user/3292
#         tmpfs                          6554932         0    6554932   0% /run/user/3211
#         tmpfs                          6554932         0    6554932   0% /run/user/3209
#         tmpfs                          6554932         0    6554932   0% /run/user/3223
#         tmpfs                          6554932         0    6554932   0% /run/user/3275
#         tmpfs                          6554932         0    6554932   0% /run/user/3235
#         tmpfs                          6554932         0    6554932   0% /run/user/3274


# rmdir 
#     - Directories can be deleted using the rmdir command - $rmdir dirname
# Syntax:
#     rmdir dirname
# output:
#     [be2371@localhost OS_LAB]$ ls
#     newdir
#     [be2371@localhost OS_LAB]$ rmdir newdir
#     [be2371@localhost OS_LAB]$ ls
#     [be2371@localhost OS_LAB]$


# cat 
#     – It displays the contents of a file - 
# Syntax:
#     $cat filename
# output:
#     [be2371@localhost OS_LAB]$ ls
#     a.txt
#     [be2371@localhost OS_LAB]$ cat a.txt
#     this is a text file
#     [be2371@localhost OS_LAB]$


# cp 
#     - It is used to copy a file - 
# Syntax:
#     $ cp source_file destination_file
# output:
#     [be2371@localhost OS_LAB]$ ls
#     a.txt  b.txt  dir
#     [be2371@localhost OS_LAB]$ cp a.txt b.txt
#     [be2371@localhost OS_LAB]$ cat a.txt
#     this is a text file
#     [be2371@localhost OS_LAB]$ cat b.txt
#     this is a text file
#     [be2371@localhost OS_LAB]$


# mv
#     - I..t .is used to change the name of a file
#     Rename files or directories
#     Move files or directories from one location to another
# Syntax:
#     $ mv old_file new_file
#     $ mv source_file target_directory/
# output:
#     [be2371@localhost OS_LAB]$ ls
#     a.txt  b.txt  dir
#     [be2371@localhost OS_LAB]$ vi a.txt
#     [be2371@localhost OS_LAB]$ ls
#     a.txt  b.txt  dir
#     [be2371@localhost OS_LAB]$ mv a.txt b.txt
#     [be2371@localhost OS_LAB]$ ls
#     b.txt  dir
#     [be2371@localhost OS_LAB]$ cat b.txt
#     this is a text file that will be renamed


# rm 
#     – It is used to delete an existing file - 
# Syntax:
#     $ rm filename
# output:
#     [be2371@localhost OS_LAB]$ ls
#     b.txt  dir
#     [be2371@localhost OS_LAB]$ rm b.txt
#     [be2371@localhost OS_LAB]$ rm -r dir
#     [be2371@localhost OS_LAB]$ ls
#     [be2371@localhost OS_LAB]$
    

# stat
#     - It is used to display file or file system status - 
# Syntax:
#     $ stat filename
# output:
#     [be2371@localhost OS_LAB]$ ls
#     a.txt
#     [be2371@localhost OS_LAB]$ stat a.txt
#     File: ‘a.txt’
#     Size: 39              Blocks: 8          IO Block: 4096   regular file
#     Device: fd02h/64770d    Inode: 3490012359  Links: 1
#     Access: (0644/-rw-r--r--)  Uid: ( 3274/  be2371)   Gid: ( 2926/  ugyr23)
#     Context: unconfined_u:object_r:user_home_t:s0
#     Access: 2025-07-25 01:28:50.050521637 +0530
#     Modify: 2025-07-25 01:28:50.050521637 +0530
#     Change: 2025-07-25 01:28:50.050521637 +0530
#     Birth: -
#     [be2371@localhost OS_LAB]$




# ln 
#     - It is used to create links between files and directories.
# Syntax:
#     $ ln [file/folder] [link file/folder name]
# output:
#     [be2371@localhost OS_LAB]$ vi a.txt
#     [be2371@localhost OS_LAB]$ ls
#     a.txt
#     [be2371@localhost OS_LAB]$ ln a.txt hardlink.txt
#     [be2371@localhost OS_LAB]$ ls
#     a.txt  hardlink.txt
#     [be2371@localhost OS_LAB]$ cat hardlink.txt
#     this a text file
#     [be2371@localhost OS_LAB]$ cat a.txt
#     this a text file
#     [be2371@localhost OS_LAB]$ mkdir dir1
#     [be2371@localhost OS_LAB]$ ln -s dir1 softlinkDir
#     [be2371@localhost OS_LAB]$ ls
#     a.txt  dir1  hardlink.txt  softlinkDir
#     [be2371@localhost OS_LAB]$


# tty 
#     – It prints the filename of the terminal connected to standard input.
# Syntax:
#     $ tty
# output:
#     [be2371@localhost OS_LAB]$ tty
#     /dev/pts/0
#     [be2371@localhost OS_LAB]$


# uname 
#     –It prints system information
# Syntax:
#     $ uname 
# output:
#     [be2371@localhost OS_LAB]$ uname
#     Linux
#     [be2371@localhost OS_LAB]$ uname -a
#     Linux localhost.localdomain 3.10.0-514.21.1.el7.x86_64 #1 SMP Thu May 25 12:04:35 CDT 2017 x86_64 x86_64 x86_64 GNU/Linux
#     [be2371@localhost OS_LAB]$


# umask 
#     – It specifies user file creation mask, implying which of the 3 permissions are to be denied to the owner,group and others.
# Syntax:
#     umask --> for viewing the curent mask
#     umask [new mask for this dir] --> for setting new mask for this dir
# output:
#     [be2371@localhost OS_LAB]$ umask
#     0022
#     [be2371@localhost OS_LAB]$ touch text.txt
#     [be2371@localhost OS_LAB]$ ls -l text.txt
#     -rw-r--r--. 1 be2371 ugyr23 0 Jul 25 01:58 text.txt
#     [be2371@localhost OS_LAB]$ umask 0077
#     [be2371@localhost OS_LAB]$ touch private.txt
#     [be2371@localhost OS_LAB]$ ls -l private.txt
#     -rw-------. 1 be2371 ugyr23 0 Jul 25 02:00 private.txt
#     [be2371@localhost OS_LAB]$


# find 
#     – It searches for files in a directory hierarchy
# Syntax:
#     $ find -flag [searchKey]
# output:
#     [be2371@localhost OS_LAB]$ ls
#     dir1  dir2  private.txt  text.txt
#     [be2371@localhost OS_LAB]$ find . -name "22.txt"
#     ./dir1/22.txt
#     ./dir2/22.txt
#     [be2371@localhost OS_LAB]$


# sort 
#     – It sorts the lines of text files
# Syntax:
#     $ sort [options] [filename]
# output:
#     [be2371@localhost OS_LAB]$ ls
#     1.txt
#     [be2371@localhost OS_LAB]$ cat 1.txt
#     a
#     k
#     d
#     s
#     c
#     e
#     1
#     3
#     4
#     2a
#     k
#     d
#     s
#     c
#     e
#     1
#     3
#     4
#     2
#     [be2371@localhost OS_LAB]$ sort 1.txt
#     1
#     1
#     2
#     2a
#     3
#     3
#     4
#     4
#     a
#     c
#     c
#     d
#     d
#     e
#     e
#     k
#     k
#     s
#     s


# ps 
#     - It displays information about the current processes.
# Syntax:
#     $ ps
# output:
#     [be2371@localhost OS_LAB]$ ps
#     PID TTY          TIME CMD
#     1860 pts/0    00:00:00 bash
#     2016 pts/0    00:00:00 ps
#     [be2371@localhost OS_LAB]$


# chmod 777 file1
#           - gives full permission to owner, group and others
# Syntax:
#     $ chmod 777 fileName
# output:
#     [be2371@localhost OS_LAB]$ touch 1.txt
#     [be2371@localhost OS_LAB]$ chmod 777 1.txt
#     [be2371@localhost OS_LAB]$ ls -l 1.txt
#     -rwxrwxrwx. 1 be2371 ugyr23 0 Jul 25 02:34 1.txt
#     [be2371@localhost OS_LAB]$


# grep 
#     - It finds specific patterns in files.
# Syntax:
#     $ grep "key" filename
# output:
#     [be2371@localhost OS_LAB]$ vi 1.txt
#     [be2371@localhost OS_LAB]$ cat 1.txt
#     hello everyone , how are you, hello, hello hello

#     [be2371@localhost OS_LAB]$ grep "hello" 1.txt
#     hello everyone , how are you, hello, hello hello
#     [be2371@localhost OS_LAB]$


# touch 
#     - It creates an empty file or updates the timestamp of an existing file.
# Syntax:
#     $ touch newFileName
# output:
#     [be2371@localhost OS_LAB]$ ls
#     1.txt
#     [be2371@localhost OS_LAB]$ touch 2.txt
#     [be2371@localhost OS_LAB]$ ls
#     1.txt  2.txt
#     [be2371@localhost OS_LAB]$


# more/less 
#     - It displays file content one screen at a time, allowing you to scroll.
# Syntax:
#     $ more filename
#     $ less filename
#     [be2371@localhost OS_LAB]$ seq 1 100 > numbers.txt
#     [be2371@localhost OS_LAB]$ more numbers.txt
#     1
#     2
#     3
#     4
#     5
#     6
#     7
#     8
#     9
#     10
#     11
#     12
#     13
#     14
#     15
#     16
#     17
#     18
#     19
#     20
#     21
#     22
#     23
#     24
#     25
#     26
#     27
#     28
#     29
#     --More--(26%)


# head/tail 
#     - It displays First/Last 10 lines of a File.
# Syntax:
#     $ head filename
#     $ tail filename
# output:
#     [be2371@localhost OS_LAB]$ ls
#     1.txt  2.txt  numbers.txt
#     [be2371@localhost OS_LAB]$ head numbers.txt
#     1
#     2
#     3
#     4
#     5
#     6
#     7
#     8
#     9
#     10
#     [be2371@localhost OS_LAB]$ tail numbers.txt
#     91
#     92
#     93
#     94
#     95
#     96
#     97
#     98
#     99
#     100
#     [be2371@localhost OS_LAB]$


# top 
#     - It dynamically displays real-time information about system statistics.
# Syntax:
#     $ top
# output:
#     [be2371@localhost OS_LAB]$ top
#     top - 02:57:11 up 276 days, 15:10,  4 users,  load average: 0.00, 0.01, 0.05
#     Tasks: 329 total,   1 running, 318 sleeping,   7 stopped,   0 zombie
#     %Cpu(s):  0.0 us,  0.0 sy,  0.0 ni,100.0 id,  0.0 wa,  0.0 hi,  0.0 si,  0.0 st
#     KiB Mem : 65549308 total, 53947724 free,  2278416 used,  9323168 buff/cache
#     KiB Swap: 32899068 total, 32899068 free,        0 used. 61730512 avail Mem
#     PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND
#     2633 be2371    20   0  157840   2436   1556 R   0.3  0.0   0:00.19 top
#     30624 root      20   0       0      0      0 S   0.3  0.0   0:04.10 kworker/u32:1
#         1 root      20   0  194444   7592   3988 S   0.0  0.0  29:34.37 systemd
#         2 root      20   0       0      0      0 S   0.0  0.0   0:25.89 kthreadd
#         3 root      20   0       0      0      0 S   0.0  0.0 360:10.52 ksoftirqd/0
#         8 root      rt   0       0      0      0 S   0.0  0.0   0:04.49 migration/0
#         9 root      20   0       0      0      0 S   0.0  0.0   0:00.00 rcu_bh
#     10 root      20   0       0      0      0 S   0.0  0.0 328:21.44 rcu_sched
#     11 root      rt   0       0      0      0 S   0.0  0.0   1:07.44 watchdog/0
#     12 root      rt   0       0      0      0 S   0.0  0.0   1:06.34 watchdog/1
#     13 root      rt   0       0      0      0 S   0.0  0.0   0:13.47 migration/1
#     14 root      20   0       0      0      0 S   0.0  0.0 260:50.21 ksoftirqd/1
#     16 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/1:0H
#     17 root      rt   0       0      0      0 S   0.0  0.0   1:00.61 watchdog/2
#     18 root      rt   0       0      0      0 S   0.0  0.0   0:08.24 migration/2
#     19 root      20   0       0      0      0 S   0.0  0.0 200:43.46 ksoftirqd/2
#     21 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/2:0H
#     22 root      rt   0       0      0      0 S   0.0  0.0   0:59.59 watchdog/3
#     23 root      rt   0       0      0      0 S   0.0  0.0   0:06.07 migration/3
#     24 root      20   0       0      0      0 S   0.0  0.0 167:21.25 ksoftirqd/3
#     26 root       0 -20       0      0      0 S   0.0  0.0   0:00.00 kworker/3:0H
#     27 root      rt   0       0      0      0 S   0.0  0.0   1:02.32 watchdog/4
#     28 root      rt   0       0      0      0 S   0.0  0.0   0:02.05 migration/4 



# kill 
#     - It terminates a Process.
# Syntax:
#     $ kill [PID]
# output:
#     [be2371@localhost OS_LAB]$ sleep 1000 &
#     [1] 9433
#     [be2371@localhost OS_LAB]$ ls
#     1.txt  2.txt  numbers.txt
#     [be2371@localhost OS_LAB]$ ps aux | grep sleep
#     root      9432  0.0  0.0 107896   600 ?        S    19:02   0:00 sleep 60
#     be2371    9433  0.0  0.0 107896   608 pts/0    S    19:03   0:00 sleep 1000
#     be2371    9436  0.0  0.0 112648   964 pts/0    S+   19:03   0:00 grep --color=auto sleep
#     [be2371@localhost OS_LAB]$ kill 9433
#     [1]+  Terminated              sleep 1000
#     [be2371@localhost OS_LAB]$ ps aux | grep sleep
#     root      9444  0.0  0.0 107896   604 ?        S    19:03   0:00 sleep 60
#     be2371    9446  0.0  0.0 112648   964 pts/0    S+   19:04   0:00 grep --color=auto sleep


# history 
#     - It displays a list of previously executed commands.
# Syntax:
#     $ history
# output:
#     [be2371@localhost OS_LAB]$ history
#     22  ls
#     23  clear
#     24  history
#     [be2371@localhost OS_LAB]$


# du 
#     - It estimates file space usage (of a file or directory).
# Syntax:
#     $ du
# output:
#     [be2371@localhost OS_LAB]$ vi 1.txt
#     [be2371@localhost OS_LAB]$ du
#     8       .
#     [be2371@localhost OS_LAB]$ ls
#     1.txt  2.txt  numbers.txt
#     [be2371@localhost OS_LAB]$ rm 1.txt
#     [be2371@localhost OS_LAB]$ du
#     4       .
#     [be2371@localhost OS_LAB]$ ls
#     2.txt  numbers.txt
#     [be2371@localhost OS_LAB]$


# ping 
#     - It tests network connectivity to a host.
# Syntax:
#     ping [hostname or IP address]
# output:
#     [be2371@localhost OS_LAB]$ ping 172.16.4.112
#     PING 172.16.4.112 (172.16.4.112) 56(84) bytes of data.
#     64 bytes from 172.16.4.112: icmp_seq=1 ttl=64 time=0.056 ms
#     64 bytes from 172.16.4.112: icmp_seq=2 ttl=64 time=0.037 ms
#     64 bytes from 172.16.4.112: icmp_seq=3 ttl=64 time=0.037 ms
#     64 bytes from 172.16.4.112: icmp_seq=4 ttl=64 time=0.037 ms
#     64 bytes from 172.16.4.112: icmp_seq=5 ttl=64 time=0.036 ms
#     64 bytes from 172.16.4.112: icmp_seq=6 ttl=64 time=0.037 ms
#     ^C
#     --- 172.16.4.112 ping statistics ---
#     6 packets transmitted, 6 received, 0% packet loss, time 4999ms
#     rtt min/avg/max/mdev = 0.036/0.040/0.056/0.007 ms
#     [be2371@localhost OS_LAB]$


# wc 
#     - It counts lines, words, and characters in a file.
# Syntax:
#     $ wc [filename]
# output:
#     [be2371@localhost OS_LAB]$ ls
#     2.txt  numbers.txt
#     [be2371@localhost OS_LAB]$ wc 2.txt
#     1 21 99 2.txt
#     [be2371@localhost OS_LAB]$


# >/>> 
#     - It redirects the standard output of a command to a file, overwriting the file if it exists.
# Syntax:
#     $ output >/>> filename
# output:
#     [be2371@localhost OS_LAB]$ echo "hello guys" > 3.txt
#     [be2371@localhost OS_LAB]$ ls
#     1.txt  2.txt  3.txt
#     [be2371@localhost OS_LAB]$ cat 3.txt
#     hello guys
#     [be2371@localhost OS_LAB]$ echo "this >> will append into the file" >> 3.txt
#     [be2371@localhost OS_LAB]$ cat 3.txt
#     hello guys
#     this >> will append into the file
#     [be2371@localhost OS_LAB]$


# | 
#     - It takes the standard output of one command and uses it as the standard input for another command.........................
# Syntax:
#     $ command1 | command2
# output:
#     [be2371@localhost OS_LAB]$ cat 1.txt
#     mango
#     apple
#     babana
#     fruits
#     coconuts
#     [be2371@localhost OS_LAB]$ cat 1.txt | sort
#     apple
#     babana
#     coconuts
#     fruits
#     mango
#     [be2371@localhost OS_LAB]$