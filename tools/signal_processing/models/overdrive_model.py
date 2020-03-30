import numpy as np
from scipy import signal

LOW_PASS_ORDER = 2
LOW_PASS_RANGE = (1000, 7000)


class OverdriveModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self.update(0, 0)

    def gain_ranges(self):
        return {'minValue': 0.0, 'maxValue': 20, 'resolution': 0.1}

    def tone_ranges(self):
        return {'minValue': 0.0, 'maxValue': 1, 'resolution': 0.01}

    def update(self, gain, tone):
        self._gain = gain
        self._tone = tone

        fc = (LOW_PASS_RANGE[1] - LOW_PASS_RANGE[0]) * self._tone + LOW_PASS_RANGE[0]
        self._sos = signal.butter(LOW_PASS_ORDER, fc, 'low', output='sos', fs=self._configuration.fs)

    def process_audio(self, x):
        if self._gain == 0:
            return x

        y = np.sign(x) * (1 - np.exp(-np.abs(x * (1 + self._gain))))
        y = signal.sosfilt(self._sos, y)
        y *= 0.75

        return y
