class ReverbModel:
    def __init__(self, configuration):
        self._configuration = configuration

    def volume_ranges(self):
        return {'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def update(self, volume):
        pass

    def process_audio(self, x):
        return x
