# minitalk

Here we go ..

### repo refs

- https://github.com/M4rrs/minitalk
- https://github.com/Ysoroko/minitalk
- https://github.com/ahkecha/minitalk

### technical refs

- https://man7.org/linux/man-pages/man2/signal.2.html
- https://man7.org/linux/man-pages/man7/signal.7.html
- http://www.cs.kent.edu/~ruttan/sysprog/lectures/signals.html

### tutorial refs

- https://linuxhint.com/signal_handlers_c_programming_language/
- https://www.geeksforgeeks.org/signals-c-language/

# Project Outline
Here's a bunch of shit I need it to do:

`server`
- must be started first
- must print it's PID on launch
- needs to be FAST
- should be able to recieve messages from several clients in a row without needing to restart
- should acknowledge every message recieved by sending a signal back to the client

`client`
- take a PID and a message/char string.
- Use ft_atoi to convert PID input to integers.
- return errors if not a valid PID.
- send the string bit by bit using SIGUSR1 and SIGUSR2 to represent 0 and 1 respectively.
