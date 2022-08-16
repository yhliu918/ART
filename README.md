# ART
Modified adaptive radix tree with upper bound implementation

original implementation linked from https://github.com/armon/libart

This version only supports 32bit integers (but easy to extend), an easy range query `upper_bound_new` is added to get the node which has the smallest key higher than (alias, greater_than) the key you query.

`example.cc` is a quick performance profiling of `upper_bound_new`.

we report a speed of ~ 157ns/record when there are 1.5M records, compiled with g++ -O3, on a Intel(R) Xeon(R) Platinum 8269CY CPU @ 2.50 machine.

