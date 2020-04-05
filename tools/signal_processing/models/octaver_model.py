import numpy as np
from scipy import signal

DOWN_OCTAVE_LOW_PASS_ORDER = 1
DOWN_OCTAVE_LOW_PASS_FC = 338
UP_OCTAVE_BAND_PASS_ORDER = 2
UP_OCTAVE_BAND_PASS_FC = (100, 1000)


class OctaverModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self._down_volume = 0
        self._up_volume = 0

        self._sos_down_octave_low_pass = signal.butter(DOWN_OCTAVE_LOW_PASS_ORDER, DOWN_OCTAVE_LOW_PASS_FC,
                                                       'low', output='sos', fs=configuration.fs)
        self._sos_up_octave_band_pass = signal.butter(UP_OCTAVE_BAND_PASS_ORDER, UP_OCTAVE_BAND_PASS_FC,
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
        down_octave = signal.sosfilt(self._sos_down_octave_low_pass, down_octave)
        down_octave *= self._down_volume

        return down_octave

    def generate_up_octave(self, x):
        up_octave = np.abs(x)
        up_octave = signal.sosfilt(self._sos_up_octave_band_pass, up_octave)
        up_octave *= 2 * self._up_volume

        return up_octave
