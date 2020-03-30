import numpy as np

from models.signals import *


class Configuration:
    def __init__(self, fs=48000):
        self.fs = fs
        self.freqz_f = np.logspace(0, np.log10(self.fs / 2), num=100)

    def signals(self):
        return [StepSignal(self.fs),
                SinSignal(self.fs),
                SinStepSignal(self.fs),
                LinearSignal(self.fs),
                SinModSignal(self.fs)]
