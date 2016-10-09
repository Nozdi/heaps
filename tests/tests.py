#!/usr/bin/env python
import sys
import random

def generic_generate(filename, heap_type, elems):
    with open(filename, 'w') as fp:
        if heap_type == 'bin':
            fp.write("1\n")
        else:
            fp.write("2\n")

        # create heap
        fp.write("1\n")
        for elem in elems:
            fp.write("2\n")
            fp.write(str(elem) + "\n")

        for _ in elems:
            fp.write("3\n")
        fp.write("9\n")
    return filename


def generate_increasing(no, heap_type):
    return generic_generate(
        "{}_{}.inc".format(no, heap_type),
        heap_type,
        xrange(1, no+1)
    )


def generate_decreasing(no, heap_type):
    return generic_generate(
        "{}_{}.dec".format(no, heap_type),
        heap_type,
        xrange(no+1, 1, -1)
    )


def generate_random(no, heap_type):
    return generic_generate(
        "{}_{}.rand".format(no, heap_type),
        heap_type,
        [random.randint(1, no) for _ in range(no)]
    )


def generate_all(no):
    generators = [generate_increasing, generate_decreasing, generate_random]
    heaps = ['fib', 'bin']
    names = []
    for h in heaps:
        for f in generators:
            names.append(f(no, h))
    return names


if __name__ == '__main__':
    all_names = [generate_all(no) for no in [1000, 10000, 100000, 1000000]]

