from PySide2.QtWidgets import QWidget, QHBoxLayout

from ui.effects.time_effect_widget import TimeEffectWidget
from ui.utils.double_slider import DoubleSlider


class CompressorWidget(TimeEffectWidget):
    def __init__(self, configuration, model):
        super().__init__(configuration, model)

    def _create_slider_widget(self):
        self._threshold_slider = DoubleSlider('Threshold', **self._model.threshold_ranges())
        self._ratio_slider = DoubleSlider('Ratio', **self._model.ratio_ranges())
        self._knee_width_slider = DoubleSlider('Knee Width', **self._model.knee_width_ranges())
        self._attack_slider = DoubleSlider('Attack', **self._model.attack_ranges())
        self._release_slider = DoubleSlider('Release', **self._model.release_ranges())

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._threshold_slider)
        hlayout.addWidget(self._ratio_slider)
        hlayout.addWidget(self._knee_width_slider)
        hlayout.addWidget(self._attack_slider)
        hlayout.addWidget(self._release_slider)
        hlayout.addStretch()

        widget = QWidget()
        widget.setLayout(hlayout)
        return widget

    def _connect_events(self):
        super()._connect_events()
        self._threshold_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._ratio_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._knee_width_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._attack_slider.valueChanged.connect(self._on_slider_valued_changed)
        self._release_slider.valueChanged.connect(self._on_slider_valued_changed)

    def _get_slider_values(self):
        return [self._threshold_slider.value(),
                self._ratio_slider.value(),
                self._knee_width_slider.value(),
                self._attack_slider.value(),
                self._release_slider.value()]
