import numpy as np


def secant(f, a, b, epsilon=10**-5):
    assert epsilon > 0
    assert f(a)*f(b) <= 0

    range_hist = [(a, b)]
    fc = epsilon + 1  # for first check

    while not np.abs(fc) <= epsilon:
        fa = f(a)
        fb = f(b)

        c = (a*fb - b*fa) / (fb-fa)
        fc = f(c)

        if fc * fa > 0:
            a = c
        else:
            b = c

        range_hist.append((a, b))

    hist = np.asarray(range_hist[:-1])
    return c, hist
