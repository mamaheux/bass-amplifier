from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.effects.time_effect_widget import TimeEffectWidget
from ui.utils.double_slider import DoubleSlider


class OctaverWidget(TimeEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._dowm_volume_slider = DoubleSlider('Octaver Down Volume', **self._model.dowm_volume_ranges())
        self._up_volume_slider = DoubleSlider('Octaver Up Volume', **self._model.up_volume_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._dowm_volume_slider)
        hlayout.addWidget(self._up_volume_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._dowm_volume_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._up_volume_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._dowm_volume_slider.value(),
                self._up_volume_slider.value()]
