import matplotlib.pyplot as plt

from PySide2.QtWidgets import QWidget, QVBoxLayout
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg


class GainPlotWidget(QWidget):
    def __init__(self, min_frequency=10, max_frequency=24000, min_gain=-20, max_gain=20):
        super().__init__()

        self._min_frequency = min_frequency
        self._max_frequency = max_frequency
        self._min_gain = min_gain
        self._max_gain = max_gain

        self._fig = plt.figure()
        self._ax = self._fig.add_subplot(111)

        self._canvas = FigureCanvasQTAgg(self._fig)

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._canvas)
        self.setLayout(vlayout)

    def update(self, f, g):
        self._ax.cla()

        self._ax.semilogx([self._min_frequency, self._max_frequency], [0, 0], '--', color='tab:orange')
        self._ax.semilogx(f, g, color='tab:blue')

        self._ax.set_xlim(self._min_frequency, self._max_frequency)
        self._ax.set_ylim(self._min_gain, self._max_gain)

        self._ax.set_xlabel('Frequency (Hz)')
        self._ax.set_ylabel('Gain (dB)')

        self._canvas.draw()
