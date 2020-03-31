import numpy as np


def sqrt_gain_db(gain_db):
    return 20 * np.log10(np.sqrt(np.power(10, gain_db / 20)))


def design_low_shelving_filter(g_db, f, q, fs):
    k = np.tan((np.pi * f) / fs);
    v0 = np.power(10.0, g_db / 20.0);
    root2 = 1.0 / q

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


def design_peak_filter(g_db, f, q, fs):
    w_c = (2 * np.pi * f / fs);
    mu = np.power(10, g_db / 20)
    k_q = 4 / (1 + mu) * np.tan(w_c / (2 * q))
    c_pk = (1 + k_q * mu) / (1 + k_q)

    b0 = c_pk
    b1 = c_pk * (-2 * np.cos(w_c) / (1 + k_q * mu))
    b2 = c_pk * (1 - k_q * mu) / (1 + k_q * mu)
    a0 = 1
    a1 = -2 * np.cos(w_c) / (1 + k_q)
    a2 = (1 - k_q) / (1 + k_q)

    return np.array([b0, b1, b2, a0, a1, a2])


def iir_comb(x, gain, delay):
    # BL = 1, FB = gain, FF = 0
    y = np.zeros(delay + x.shape[0])

    for i in range(x.shape[0]):
        y[i + delay] = x[i] + gain * y[i]

    y = y[delay:]

    return y


def feedback_comb(x, gain, delay):
    # BL = 0, FB = gain, FF = 1
    y = np.zeros(delay + x.shape[0])

    for i in range(x.shape[0]):
        y[i + delay] = x[i] + gain * y[i]

    y = y[:x.shape[0]]

    return y


def all_pass_comb(x, gain, delay):
    # BL = gain, FB = -gain, FF = 1
    delayed_s = np.zeros(delay + x.shape[0])
    y = np.zeros_like(x)
    for i in range(x.shape[0]):
        delayed_s[i + delay] = x[i] + -gain * delayed_s[i]
        y[i] = gain * delayed_s[i + delay] + delayed_s[i]

    return y
