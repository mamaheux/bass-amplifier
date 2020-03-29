import numpy as np
from scipy import signal

from models.utils import sqrt_gain_db, design_high_shelving_filter

class CompressorModel:
    def __init__(self, configuration):
        self._configuration = configuration

    def threshold_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def ratio_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def knee_width_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def attack_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def release_ranges(self):
        return { 'minValue': 0.1, 'maxValue': 2, 'resolution': 0.1}

    def update(self, threshold, ratio, knee_width, attack, release):
        pass

    def process_audio(self, x):
        return x
