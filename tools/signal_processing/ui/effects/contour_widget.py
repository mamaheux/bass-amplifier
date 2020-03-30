from PySide2.QtWidgets import QWidget, QHBoxLayout, QGroupBox

from ui.effects.freq_effect_widget import FreqEffectWidget
from ui.utils.double_slider import DoubleSlider


class ContourWidget(FreqEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._gain_slider = DoubleSlider('Gain (dB)', **self._model.gain_ranges())

        self._low_group_box = QGroupBox('Low')
        self._low_freq_slider = DoubleSlider('Freq (Hz)', **self._model.low_freq_ranges())
        self._low_q_slider = DoubleSlider('Q', **self._model.low_q_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._low_freq_slider)
        hlayout.addWidget(self._low_q_slider)
        self._low_group_box.setLayout(hlayout)

        self._high_group_box = QGroupBox('High')
        self._high_freq_slider = DoubleSlider('Freq (Hz)', **self._model.high_freq_ranges())
        self._high_q_slider = DoubleSlider('Q', **self._model.high_q_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._high_freq_slider)
        hlayout.addWidget(self._high_q_slider)
        self._high_group_box.setLayout(hlayout)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._gain_slider)
        hlayout.addWidget(self._low_group_box)
        hlayout.addWidget(self._high_group_box)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._low_freq_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._low_q_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._high_freq_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._high_q_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._gain_slider.value(),
                self._low_freq_slider.value(),
                self._low_q_slider.value(),
                self._high_freq_slider.value(),
                self._high_q_slider.value()]
