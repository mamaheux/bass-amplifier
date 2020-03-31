import numpy as np

from models.utils import feedback_comb, all_pass_comb


class ReverbModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self._volume = 0.0

        self._feedback_comb_delays = np.array([0.0041224, 0.0050429, 0.0369579, 0.0398238, 0.0167182, 0.0183006])
        self._feedback_comb_delays *= self._configuration.fs
        self._feedback_comb_delays = self._feedback_comb_delays.astype(int)
        self._feedback_comb_gain = 0.5

        self._all_pass_gain = 0.7
        self._all_pass_delay = int(0.08 * self._configuration.fs)

    def volume_ranges(self):
        return {'minValue': 0.0, 'maxValue': 0.9, 'resolution': 0.01}

    def update(self, volume):
        self._volume = volume

    def process_audio(self, x):
        if self._volume == 0:
            return 0.5 * x

        y = np.zeros_like(x)

        for i in range(len(self._feedback_comb_delays)):
            y += feedback_comb(x, self._volume, self._feedback_comb_delays[i])

        y *= (1 / len(self._feedback_comb_delays))

        y = all_pass_comb(y, self._volume, self._all_pass_delay)

        return 0.5 * x + self._volume * y
