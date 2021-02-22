import numpy as np


def newton(f, x0, df, epsilon=10**-5, c=1):
    assert epsilon > 0

    xk = x0
    fk = f(x0)
    x_hist = [x0]

    while not np.abs(fk) <= epsilon:
        xk = xk - c * fk / df(xk)
        fk = f(xk)
        x_hist.append(xk)

    return xk, np.asarray(x_hist)
