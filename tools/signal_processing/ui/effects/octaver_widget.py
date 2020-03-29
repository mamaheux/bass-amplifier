from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout

from ui.utils.double_slider import DoubleSlider
from ui.utils.time_plot_widget import TimePlotWidget

class OctaverWidget(QWidget):
    def __init__(self, configuration, model):
        super().__init__()
        self._configuration = configuration
        self._model = model

        self._create_ui()
        self._connect_events()
        self._on_slider_valued_changed(0)

    def _create_ui(self):
        self._dowm_volume_slider = DoubleSlider('Octaver Down Volume', **self._model.dowm_volume_ranges())
        self._up_volume_slider = DoubleSlider('Octaver Up Volume', **self._model.up_volume_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._dowm_volume_slider)
        hlayout.addWidget(self._up_volume_slider)
        hlayout.addStretch()

        self._plot = TimePlotWidget(self._configuration.signals())

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addLayout(hlayout)
        self.setLayout(vlayout)

    def _connect_events(self):
        self._dowm_volume_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._up_volume_slider.valueChanged.connect(self._on_slider_valued_changed)

    @Slot()
    def _on_slider_valued_changed(self, _):
        self._model.update(self._dowm_volume_slider.value(),
                           self._up_volume_slider.value())

        t, s = self._plot.signal().signal()
        s = self._model.process_audio(s)

        self._plot.update(t, s)
