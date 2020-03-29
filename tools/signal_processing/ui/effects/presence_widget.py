from PySide2.QtCore import Qt, Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QGroupBox

from ui.utils.double_slider import DoubleSlider
from ui.utils.gain_plot_widget import GainPlotWidget

class PresenceWidget(QWidget):
    def __init__(self, configuration, model):
        super().__init__()
        self._configuration = configuration
        self._model = model

        self._create_ui()
        self._connect_events()
        self._on_slider_valued_changed(0)

    def _create_ui(self):
        self._gain_slider = DoubleSlider('Gain (dB)', **self._model.gain_ranges())
        self._freq_slider = DoubleSlider('Freq (Hz)', **self._model.freq_ranges())
        self._q_slider = DoubleSlider('Q', **self._model.q_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._gain_slider)
        hlayout.addWidget(self._freq_slider)
        hlayout.addWidget(self._q_slider)
        hlayout.addStretch()

        self._plot = GainPlotWidget(max_frequency=self._configuration.fs // 2)

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addLayout(hlayout)
        self.setLayout(vlayout)

    def _connect_events(self):
        self._gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._freq_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._q_slider.valueChanged.connect(self._on_slider_valued_changed)

    @Slot()
    def _on_slider_valued_changed(self, _):
        f, g = self._model.update(self._gain_slider.value(),
                                  self._freq_slider.value(),
                                  self._q_slider.value())
        self._plot.update(f, g)





