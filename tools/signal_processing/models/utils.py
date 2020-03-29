import numpy as np

def sqrt_gain_db(gain_db):
    return 20 * np.log10(np.sqrt(np.power(10, gain_db / 20)))

def design_low_shelving_filter(g_db, f, q, fs):
    k = np.tan((np.pi * f) / fs);
    v0 = np.power(10.0, g_db / 20.0);
    root2 =  1.0 / q

    if v0 < 1:
        v0 = 1 / v0

    if g_db > 0:
        b0 = (1 + np.sqrt(v0) * root2 * k + v0 * k * k) / (1 + root2 * k + k * k)
        b1 = (2 * (v0 * k * k - 1)) / (1 + root2 * k + k * k)
        b2 = (1 - np.sqrt(v0) * root2 * k + v0 * k * k) / (1 + root2 * k + k * k)
        a0 = 1
        a1 = (2 * (k * k - 1)) / (1 + root2 * k + k * k)
        a2 = (1 - root2 * k + k * k) / (1 + root2 * k + k * k)
    elif g_db < 0:
        b0 = (1 + root2 * k + k * k) / (1 + root2 * np.sqrt(v0) * k + v0 * k * k)
        b1 = (2 * (k * k - 1)) / (1 + root2 * np.sqrt(v0) * k + v0 * k * k)
        b2 = (1 - root2 * k + k * k) / (1 + root2 * np.sqrt(v0) * k + v0 * k * k)
        a0 = 1
        a1 = (2 * (v0 * k * k - 1)) / (1 + root2 * np.sqrt(v0) * k + v0 * k * k)
        a2 = (1 - root2 * np.sqrt(v0) * k + v0 * k * k) / (1 + root2 * np.sqrt(v0) * k + v0 * k * k)
    else:
        b0 = 1
        b1 = 0
        b2 = 0
        a0 = 1
        a1 = 0
        a2 = 0

    return np.array([b0, b1, b2, a0, a1, a2])

def design_high_shelving_filter(g_db, f, q, fs):
    k = np.tan(np.pi * f / fs)
    v0 = np.power(10, g_db / 20)
    root2 = 1 / q

    if v0 < 1:
        v0 = 1 / v0

    if g_db > 0:
        b0 = (v0 + root2 * np.sqrt(v0) * k + k * k) / (1 + root2 * k + k * k)
        b1 = (2 * (k * k - v0)) / (1 + root2 * k + k * k)
        b2 = (v0 - root2 * np.sqrt(v0) * k + k * k) / (1 + root2 * k + k * k)
        a0 = 1
        a1 = (2 * (k * k - 1)) / (1 + root2 * k + k * k)
        a2 = (1 - root2 * k + k * k) / (1 + root2 * k + k * k)
    elif g_db < 0:
        b0 = (1 + root2 * k + k * k) / (v0 + root2 * np.sqrt(v0) * k + k * k)
        b1 = (2 * (k * k - 1)) / (v0 + root2 * np.sqrt(v0) * k + k * k)
        b2 = (1 - root2 * k + k * k) / (v0 + root2 * np.sqrt(v0) * k + k * k)
        a0 = 1
        a1 = (2 * ((k * k) / v0 - 1)) / (1 + root2 / np.sqrt(v0) * k + (k * k) / v0)
        a2 = (1 - root2 / np.sqrt(v0) * k + (k * k) / v0) / (1 + root2 / np.sqrt(v0) * k + (k * k) / v0)
    else:
        b0 = 1
        b1 = 0
        b2 = 0
        a0 = 1
        a1 = 0
        a2 = 0

    return np.array([b0, b1, b2, a0, a1, a2])

