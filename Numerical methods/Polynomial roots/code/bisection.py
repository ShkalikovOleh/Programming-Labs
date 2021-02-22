import numpy as np


def bisection(f, a, b, epsilon=10**-5):
    assert f(a)*f(b) <= 0
    assert epsilon > 0

    range_hist = [(a, b)]
    while not np.abs(b-a) <= epsilon:
        c = (a + b) / 2
        fc = f(c)
        if fc * f(a) > 0:
            a = c
        else:
            b = c
        range_hist.append((a, b))

    c = (a + b) / 2
    hist = np.asarray(range_hist)
    return c, hist
