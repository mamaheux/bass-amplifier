import numpy as np
from scipy import signal


class EqModel:
    def __init__(self, configuration):
        self._configuration = configuration

        self._sos = np.array([[1, 0, 0, 1, 0, 0]], dtype=float)

    def update(self, low_gain_db, low_freq, low_q,
               low_mid_gain_db, low_mid_freq, low_mid_q,
               high_mid_gain_db, high_mid_freq, high_mid_q,
               high_gain_db, high_freq, high_q):
        f, h = signal.sosfreqz(self._sos, worN=self._configuration.freqz_f, fs=self._configuration.fs)
        return f, 20 * np.log10(np.abs(h))

    def process_audio(self, x):
        return signal.sosfilt(self._sos, x)
