This is a dumb program that I can use to get podcast stats from my CloudFront logs, displays the amount of downloads per podcast.

It does no more than `find . -type f -exec gzcat {} \; | egrep -o 'pip\d+.mp3' | sort | uniq -c` but boy, this one is so much faster (is exec syscall making it slow?). However, the main purpose was to get hands on with C, zlib, stdlib and etc.
