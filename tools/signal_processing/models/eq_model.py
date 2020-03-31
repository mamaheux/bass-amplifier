import numpy as np
from scipy import signal


class EqModel:
    def __init__(self, configuration):
        self._configuration = configuration

        self._sos = np.array([[1, 0, 0, 1, 0, 0]], dtype=float)

    def gain_ranges(self):
        return {'minValue': -20, 'maxValue': 20, 'resolution': 0.1}

    def update(self, low_gain_db, low_mid_gain_db, high_mid_gain_db, high_gain_db):
        f, h = signal.sosfreqz(self._sos, worN=self._configuration.freqz_f, fs=self._configuration.fs)
        return f, 20 * np.log10(np.abs(h))

    def process_audio(self, x):
        return signal.sosfilt(self._sos, x)