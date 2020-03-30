from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout

from ui.utils.gain_plot_widget import GainPlotWidget

class FreqEffectWidget(QWidget):
    def __init__(self, configuration, model):
        super().__init__()
        self._configuration = configuration
        self._model = model
        self._create_ui()
        self._connect_events()
        self._on_slider_valued_changed(0)

    def _create_ui(self):
        slider_widget = self._create_slider_widget()
        slider_widget.setMaximumHeight(300)

        self._plot = GainPlotWidget(max_frequency=self._configuration.fs // 2)

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addWidget(slider_widget)
        self.setLayout(vlayout)

    def _connect_events(self):
        pass

    @Slot()
    def _on_slider_valued_changed(self, _):
        f, g = self._model.update(*self._get_slider_values())
        self._plot.update(f, g)

    def model(self):
        return self._model
