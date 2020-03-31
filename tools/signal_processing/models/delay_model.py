from models.utils import iir_comb


class DelayModel:
    def __init__(self, configuration):
        self._configuration = configuration
        self._delay = 0
        self._volume = 0

    def delay_ranges(self):
        return {'minValue': 0.0, 'maxValue': 2, 'resolution': 0.01}

    def volume_ranges(self):
        return {'minValue': 0.0, 'maxValue': 0.5, 'resolution': 0.01}

    def update(self, delay, volume):
        self._delay = int(delay * self._configuration.fs)
        self._volume = volume

    def process_audio(self, x):
        return iir_comb(x, self._volume, self._delay)
