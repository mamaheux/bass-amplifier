import numpy as np
from scipy import signal

from models.utils import sqrt_gain_db, design_low_shelving_filter, design_high_shelving_filter

class ContourModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self._sos = np.array([[1, 0, 0, 1, 0, 0],
                              [1, 0, 0, 1, 0, 0],
                              [1, 0, 0, 1, 0, 0],
                              [1, 0, 0, 1, 0, 0],
                              [1, 0, 0, 1, 0, 0]], dtype=float)

    def gain_ranges(self):
        return { 'minValue': 0, 'maxValue': 20, 'resolution': 0.1}

    def low_freq_ranges(self):
        return { 'minValue': 50, 'maxValue': self._configuration.fs // 40, 'resolution': 10}

    def low_q_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def high_freq_ranges(self):
        return { 'minValue': self._configuration.fs // 40, 'maxValue': self._configuration.fs // 8, 'resolution': 10}

    def high_q_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def update(self, gain_db, low_freq, low_q, high_freq, high_q):
        gain_db = sqrt_gain_db(gain_db)
        self._sos[0] = design_low_shelving_filter(gain_db, low_freq, low_q, self._configuration.fs)
        self._sos[1] = self._sos[0]
        self._sos[2] = design_high_shelving_filter(gain_db, high_freq, high_q, self._configuration.fs)
        self._sos[3] = self._sos[2]
        self._sos[4][0] = 1 / (np.power(10, gain_db / 20)) # Global gain

        f, h = signal.sosfreqz(self._sos, worN=self._configuration.freqz_f, fs=self._configuration.fs)
        return f, 20 * np.log10(np.abs(h))

    def process_audio(self, x):
        return signal.sosfilt(self._sos, x)

