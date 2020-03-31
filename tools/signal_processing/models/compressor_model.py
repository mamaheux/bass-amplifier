import numpy as np

ATTACK = 0.995
RELEASE = 0.9997


class CompressorModel:
    def __init__(self, configuration):
        self._configuration = configuration

        self._threshold = 0
        self._ratio = 0

    def threshold_ranges(self):
        return {'minValue': 0.01, 'maxValue': 1, 'resolution': 0.01}

    def ratio_ranges(self):
        return {'minValue': 0.1, 'maxValue': 1.0, 'resolution': 0.01}

    def update(self, threshold, ratio):
        self._threshold = threshold
        self._ratio = ratio

    def process_audio(self, x):
        level = self._calculate_level(x)
        c = np.ones_like(level)
        c[level > self._threshold] = self._ratio * self._threshold / level[level > self._threshold] + (1 - self._ratio)

        return x * c

    def _calculate_level(self, x):
        level = np.zeros(x.shape[0] + 1)

        for i in range(x.shape[0]):
            if x[i] > level[i]:
                level[i + 1] = ATTACK * level[i] + (1 - ATTACK) * x[i]
            else:
                level[i + 1] = RELEASE * level[i] + (1 - RELEASE) * x[i]

        return level[1:]
