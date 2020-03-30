from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.effects.time_effect_widget import TimeEffectWidget
from ui.utils.double_slider import DoubleSlider


class OverdriveWidget(TimeEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._gain_slider = DoubleSlider('Gain', **self._model.gain_ranges())
        self._tone_slider = DoubleSlider('Tone', **self._model.tone_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._gain_slider)
        hlayout.addWidget(self._tone_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._gain_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._tone_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._gain_slider.value(),
                self._tone_slider.value()]
