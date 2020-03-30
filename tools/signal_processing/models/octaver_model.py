import numpy as np
from scipy import signal

OCTAVE_DOWN_LOW_PASS_ORDER = 1
OCTAVE_DOWN_LOW_PASS_FC = 338
OCTAVE_UP_BAND_PASS_ORDER = 4
OCTAVE_UP_BAND_PASS_FC = (100, 2000)


class OctaverModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self._down_volume = 0
        self._up_volume = 0

        self._sos_octave_down_low_pass = signal.butter(OCTAVE_DOWN_LOW_PASS_ORDER, OCTAVE_DOWN_LOW_PASS_FC,
                                                       'low', output='sos', fs=configuration.fs)
        self._sos_octave_up_band_pass = signal.butter(OCTAVE_UP_BAND_PASS_ORDER, OCTAVE_UP_BAND_PASS_FC,
                                                      'bandpass', output='sos', fs=configuration.fs)

    def dowm_volume_ranges(self):
        return {'minValue': 0.0, 'maxValue': 1, 'resolution': 0.01}

    def up_volume_ranges(self):
        return {'minValue': 0.0, 'maxValue': 1, 'resolution': 0.01}

    def update(self, dowm_volume, up_volume):
        self._down_volume = dowm_volume
        self._up_volume = up_volume

    def process_audio(self, x):
        down_octave = self.generate_down_octave(x)
        up_octave = self.generate_up_octave(x)

        scale_factor = 1 / (self._down_volume + self._up_volume + 1)

        return scale_factor * (x + up_octave + down_octave)

    def generate_down_octave(self, x):
        offsetted_x = x + 1

        c = np.zeros_like(x)
        c[offsetted_x > 1] = 1

        c_half = np.zeros_like(x)

        actual_value = 0
        for i in range(len(c) - 1):
            if c[i] == 0 and c[i + 1] == 1:
                actual_value = (actual_value + 1) % 2

            c_half[i] = actual_value

        c_half[-1] = c_half[-2]

        down_octave = x.copy()
        down_octave[c_half == 0] = -x[c_half == 0]
        down_octave = signal.sosfilt(self._sos_octave_down_low_pass, down_octave)
        down_octave *= self._down_volume

        return down_octave

    def generate_up_octave(self, x):
        up_octave = np.abs(x)
        up_octave = signal.sosfilt(self._sos_octave_up_band_pass, up_octave)
        up_octave *= 2 * self._up_volume

        return up_octave
