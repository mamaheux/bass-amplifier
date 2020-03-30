import numpy as np


class DelayModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self._delay = 0
        self._volume = 0

    def delay_ranges(self):
        return {'minValue': 0.0, 'maxValue': 2, 'resolution': 0.01}

    def volume_ranges(self):
        return {'minValue': 0.0, 'maxValue': 0.9, 'resolution': 0.01}

    def update(self, delay, volume):
        self._delay = int(delay * self._configuration.fs)
        self._volume = volume

    def process_audio(self, x):
        y = np.zeros(self._delay + x.shape[0])

        for i in range(x.shape[0]):
            y[i + self._delay] = x[i] + self._volume * y[i]

        y = y[self._delay:]

        return y
