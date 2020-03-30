from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.utils.double_slider import DoubleSlider
from ui.effects.time_effect_widget import TimeEffectWidget

class DelayWidget(TimeEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._delay_slider = DoubleSlider('Delay (s)', **self._model.delay_ranges())
        self._volume_slider = DoubleSlider('Volume', **self._model.volume_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._delay_slider)
        hlayout.addWidget(self._volume_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._delay_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._volume_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._delay_slider.value(),
                self._volume_slider.value()]
