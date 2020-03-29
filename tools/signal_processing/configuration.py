import numpy as np


class Configuration:
    def __init__(self, fs=48000):
        self.fs = fs
        self.freqz_f = np.logspace(0, np.log10(self.fs / 2))
