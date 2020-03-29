

class OverdriveModel:
    def __init__(self, configuration):
        self._configuration = configuration

    def gain_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def tone_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def update(self, gain, tone):
        pass

    def process_audio(self, x):
        return x
