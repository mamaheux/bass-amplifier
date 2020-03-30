from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout

from ui.utils.double_slider import DoubleSlider
from ui.utils.time_plot_widget import TimePlotWidget

class OverdriveWidget(QWidget):
    def __init__(self, configuration, model):
        super().__init__()
        self._configuration = configuration
        self._model = model

        self._create_ui()
        self._connect_events()
        self._on_slider_valued_changed(0)

    def _create_ui(self):
        self._gain_slider = DoubleSlider('Gain', **self._model.gain_ranges())
        self._tone_slider = DoubleSlider('Tone', **self._model.tone_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._gain_slider)
        hlayout.addWidget(self._tone_slider)
        hlayout.addStretch()

        self._plot = TimePlotWidget(self._configuration.signals())

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addLayout(hlayout)
        self.setLayout(vlayout)

    def _connect_events(self):
        self._gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._tone_slider.valueChanged.connect(self._on_slider_valued_changed)

        self._plot.signalChanged.connect(self._on_signal_changed)

    @Slot()
    def _on_slider_valued_changed(self, _):
        self._update_model()
        self._update_plot()

    @Slot()
    def _on_signal_changed(self):
        self._update_plot()

    def _update_model(self):
        self._model.update(self._gain_slider.value(),
                           self._tone_slider.value())

    def _update_plot(self):
        t, s = self._plot.signal().signal()
        s = self._model.process_audio(s)

        self._plot.update(t, s)
