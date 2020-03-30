from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout

from ui.utils.time_plot_widget import TimePlotWidget


class TimeEffectWidget(QWidget):
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

        self._plot = TimePlotWidget(self._configuration.signals())

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addWidget(slider_widget)
        self.setLayout(vlayout)

    def _connect_events(self):
        self._plot.signalChanged.connect(self._on_signal_changed)

    @Slot()
    def _on_slider_valued_changed(self, _):
        self._update_model()
        self._update_plot()

    @Slot()
    def _on_signal_changed(self):
        self._update_plot()

    def _update_model(self):
        self._model.update(*self._get_slider_values())

    def _update_plot(self):
        t, s = self._plot.signal().signal()
        s = self._model.process_audio(s)

        self._plot.update(t, s)

    def model(self):
        return self._model
