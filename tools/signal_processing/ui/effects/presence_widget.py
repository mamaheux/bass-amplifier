from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.utils.double_slider import DoubleSlider
from ui.effects.freq_effect_widget import FreqEffectWidget

class PresenceWidget(FreqEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._gain_slider = DoubleSlider('Gain (dB)', **self._model.gain_ranges())
        self._freq_slider = DoubleSlider('Freq (Hz)', **self._model.freq_ranges())
        self._q_slider = DoubleSlider('Q', **self._model.q_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._gain_slider)
        hlayout.addWidget(self._freq_slider)
        hlayout.addWidget(self._q_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._freq_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._q_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._gain_slider.value(),
                self._freq_slider.value(),
                self._q_slider.value()]
