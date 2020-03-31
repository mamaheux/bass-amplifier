from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.effects.freq_effect_widget import FreqEffectWidget
from ui.utils.double_slider import DoubleSlider


class EqWidget(FreqEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)
        self._low_gain_slider.set_value(0)
        self._low_mid_gain_slider.set_value(0)
        self._high_mid_gain_slider.set_value(0)
        self._high_gain_slider.set_value(0)

    def _create_slider_widget(self):
        self._low_gain_slider = DoubleSlider('Low Gain (dB)', **self._model.gain_ranges())
        self._low_mid_gain_slider = DoubleSlider('Low Mid Gain (dB)', **self._model.gain_ranges())
        self._high_mid_gain_slider = DoubleSlider('High Mid Gain (dB)', **self._model.gain_ranges())
        self._high_gain_slider = DoubleSlider('High Gain (dB)', **self._model.gain_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._low_gain_slider)
        hlayout.addWidget(self._low_mid_gain_slider)
        hlayout.addWidget(self._high_mid_gain_slider)
        hlayout.addWidget(self._high_gain_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._low_gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._low_mid_gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._high_mid_gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._high_gain_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._low_gain_slider.value(),
                self._low_mid_gain_slider.value(),
                self._high_mid_gain_slider.value(),
                self._high_gain_slider.value()]
