## Some code, intended to be a firmware of a vacuum cleaner (can't recall it's model though...)

Currently, the only thing it can do is reading PORTD 3 to 5 pins (assumed to indicate the power mode) and throw in the UART the answer: low, medium, high or the exact value, which was read.

Connect to UART and send query to fetch the power value:
```
$ microcom -p /dev/ttyS0 -s 9600
power
```
By the way, haven't you noticed that there's a space at the end of the second prompt? It's important, cause commands are partitioned by spaces, so, unless you type a space at the end of your command, it is considered incomplete. For example, two consecutive power-queries will look like this `power power ` with spaces in between and at the end.
