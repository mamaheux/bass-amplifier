import decimal

from PySide2.QtCore import Qt, Slot, Signal
from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QLabel, QSlider


class DoubleSlider(QWidget):
    valueChanged = Signal(float)

    def __init__(self, title, minValue=0, maxValue=100, resolution=1):
        super().__init__()
        self._min = minValue
        self._max = maxValue
        self._resolution = resolution
        self._decimal_count = max(0, -decimal.Decimal(str(resolution)).as_tuple().exponent)

        self._slider = QSlider(Qt.Vertical)
        self._slider.setRange(int(self._min / self._resolution), int(self._max / self._resolution))
        self._slider.valueChanged.connect(self._on_slider_valued_changed)

        self._min_label = QLabel(str(self._min))
        self._max_label = QLabel(str(self._max))
        self._value_label = QLabel(str(self._slider.value() * self._resolution))

        label_layout = QVBoxLayout()
        label_layout.addWidget(self._max_label, 0, Qt.AlignRight | Qt.AlignTop)
        label_layout.addWidget(self._value_label, 0, Qt.AlignRight | Qt.AlignCenter)
        label_layout.addWidget(self._min_label, 0, Qt.AlignRight | Qt.AlignBottom)

        slider_label_layout = QHBoxLayout()
        slider_label_layout.addLayout(label_layout)
        slider_label_layout.addWidget(self._slider)

        vlayout = QVBoxLayout()
        vlayout.addWidget(QLabel(title), 0, Qt.AlignRight)
        vlayout.addLayout(slider_label_layout)
        self.setLayout(vlayout)

    @Slot()
    def _on_slider_valued_changed(self, _):
        self._value_label.setText(('{:.' + str(self._decimal_count) + 'f}').format(self.value()))
        self.valueChanged.emit(self.value())

    def value(self):
        return self._slider.value() * self._resolution

    def set_value(self, value):
        return self._slider.setValue(value / self._resolution)
