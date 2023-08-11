from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.effects.time_effect_widget import TimeEffectWidget
from ui.utils.double_slider import DoubleSlider


class PitchShiftWidget(TimeEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._pitch_step_slider = DoubleSlider('Pitch Step', **self._model.pitch_step_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._pitch_step_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._pitch_step_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._pitch_step_slider.value()]
