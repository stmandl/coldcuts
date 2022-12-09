#!/usr/bin/env python

import random


# Sieve of Eratosthenes
# Code by David Eppstein, UC Irvine, 28 Feb 2002
# http://code.activestate.com/recipes/117119/

def gen_primes():
    """ Generate an infinite sequence of prime numbers.
    """
    # Maps composites to primes witnessing their compositeness.
    # This is memory efficient, as the sieve is not "run forward"
    # indefinitely, but only as long as required by the current
    # number being tested.
    #
    D = {}

    # The running integer that's checked for primeness
    q = 2

    while True:
        if q not in D:
            # q is a new prime.
            # Yield it and mark its first multiple that isn't
            # already marked in previous iterations
            #
            yield q
            D[q * q] = [q]
        else:
            # q is composite. D[q] is the list of primes that
            # divide it. Since we've reached q, we no longer
            # need it in the map, but we'll mark the next
            # multiples of its witnesses to prepare for larger
            # numbers
            #
            for p in D[q]:
                D.setdefault(p + q, []).append(p)
            del D[q]

        q += 1

N = 10000




num_primes = 10000
primes_n = []
i = 0
for p in gen_primes():
    primes_n.append(p)
    i += 1
    if i == num_primes:
        break
numbers = []
for _ in range(N):
    numbers.append(str(random.randrange(1,2000000)))
    # k = random.randrange(1, num_primes)
    # f = random.choices(primes_n, k=k)
    # n = 1
    # for x in f:
    #     n *= x
    # if x < 2000000:
    #     numbers.append(str(x))

s = str(len(numbers))+"\n"
s += " ".join(numbers)

print(s)

