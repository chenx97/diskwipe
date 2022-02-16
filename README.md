# diskwipe
Fill your drive with `0xffff` because why not

It's also gonna run multi-threaded, with a ctrl-c handler that only works
under some assumptions. (i.e. that the shell only sends SIGINT)

## Build

`make -j$(nproc)`

## TODO

- [ ] load balancing job server
