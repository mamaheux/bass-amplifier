import numpy as np
from scipy import signal

from models.utils import design_peak_filter

FC = [40, 80, 160, 315, 630, 1250, 2500, 5000]
R = 2

LOW_INDEXES = [0, 1]
LOW_MID_INDEXES = [2, 3]
HIGH_MID_INDEXES = [4, 5]
HIGH_INDEXES = [6, 7]


class EqModel:
    def __init__(self, configuration):
        self._configuration = configuration

        self._sos = np.zeros((len(FC), 6), dtype=float)
        self._inv_b = self._calculate_inv_b()

    def gain_ranges(self):
        return {'minValue': -12, 'maxValue': 12, 'resolution': 0.1}

    def update(self, low_gain_db, low_mid_gain_db, high_mid_gain_db, high_gain_db):
        g_db = np.zeros_like(FC, dtype=float)
        g_db[LOW_INDEXES] = low_gain_db
        g_db[LOW_MID_INDEXES] = low_mid_gain_db
        g_db[HIGH_MID_INDEXES] = high_mid_gain_db
        g_db[HIGH_INDEXES] = high_gain_db
        g_db = self._inv_b.dot(g_db)

        self._sos = self._design_sos(g_db)
        f, h = signal.sosfreqz(self._sos, worN=self._configuration.freqz_f, fs=self._configuration.fs)

        return f, 20 * np.log10(np.abs(h))

    def process_audio(self, x):
        return signal.sosfilt(self._sos, x)

    def _calculate_inv_b(self):
        g_db = 10

        sos = self._design_sos(g_db * np.ones_like(FC))

        b = np.zeros((len(FC), len(FC)))
        for i in range(len(FC)):
            f, h = signal.sosfreqz(sos[i, :], worN=FC, fs=self._configuration.fs)
            b[i] = 20 * np.log10(np.abs(h)) / g_db

        return np.linalg.inv(b)

    def _design_sos(self, g_db):
        sos = np.zeros((len(FC), 6), dtype=float)

        for i in range(len(FC)):
            q = np.sqrt(R) / (R - 1)
            sos[i] = design_peak_filter(g_db[i], FC[i], q, self._configuration.fs)

        return sos
