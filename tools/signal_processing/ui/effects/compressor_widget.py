from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout

from ui.utils.double_slider import DoubleSlider
from ui.utils.time_plot_widget import TimePlotWidget

class CompressorWidget(QWidget):
    def __init__(self, configuration, model):
        super().__init__()
        self._configuration = configuration
        self._model = model

        self._create_ui()
        self._connect_events()
        self._on_slider_valued_changed(0)

    def _create_ui(self):
        self._threshold_slider = DoubleSlider('Threshold', **self._model.threshold_ranges())
        self._ratio_slider = DoubleSlider('Ratio', **self._model.ratio_ranges())
        self._knee_width_slider = DoubleSlider('Knee Width', **self._model.knee_width_ranges())
        self._attack_slider = DoubleSlider('Attack', **self._model.attack_ranges())
        self._release_slider = DoubleSlider('Release', **self._model.release_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._threshold_slider)
        hlayout.addWidget(self._ratio_slider)
        hlayout.addWidget(self._knee_width_slider)
        hlayout.addWidget(self._attack_slider)
        hlayout.addWidget(self._release_slider)
        hlayout.addStretch()

        self._plot = TimePlotWidget(self._configuration.signals())

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addLayout(hlayout)
        self.setLayout(vlayout)

    def _connect_events(self):
        self._threshold_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._ratio_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._knee_width_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._attack_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._release_slider.valueChanged.connect(self._on_slider_valued_changed)

        self._plot.signalChanged.connect(self._on_signal_changed)

    @Slot()
    def _on_slider_valued_changed(self, _):
        self._update_model()
        self._update_plot()

    @Slot()
    def _on_signal_changed(self):
        self._update_plot()

    def _update_model(self):
        self._model.update(self._threshold_slider.value(),
                           self._ratio_slider.value(),
                           self._knee_width_slider.value(),
                           self._attack_slider.value(),
                           self._release_slider.value())

    def _update_plot(self):
        t, s = self._plot.signal().signal()
        s = self._model.process_audio(s)

        self._plot.update(t, s)
