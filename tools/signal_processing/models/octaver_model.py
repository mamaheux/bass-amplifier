

class OctaverModel:
    def __init__(self, configuration):
        self._configuration = configuration

    def dowm_volume_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def up_volume_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def update(self, dowm_volume, up_volume):
        pass

    def process_audio(self, x):
        return x
