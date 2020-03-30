import matplotlib.pyplot as plt

from PySide2.QtCore import Slot, Signal
from PySide2.QtWidgets import QWidget, QHBoxLayout, QVBoxLayout, QFormLayout, QComboBox, QDoubleSpinBox
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg


class TimePlotWidget(QWidget):
    signalChanged = Signal()

    def __init__(self, signals):
        super().__init__()
        self._signals = signals

        self._create_ui()
        self._signal_combo_box.setCurrentIndex(1)
        self._signal_combo_box.setCurrentIndex(0)

    def _create_ui(self):

        self._fig = plt.figure()
        self._ax = self._fig.add_subplot(111)

        self._canvas = FigureCanvasQTAgg(self._fig)

        self._signal_combo_box = self._create_signal_combo_box()
        self._signal_parameter_layout = QFormLayout()
        self._parameter_spin_boxes = []

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._signal_combo_box)
        vlayout.addLayout(self._signal_parameter_layout)

        parameter_widget = QWidget()
        parameter_widget.setLayout(vlayout)
        parameter_widget.setMaximumWidth(200)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._canvas)
        hlayout.addWidget(parameter_widget)
        self.setLayout(hlayout)

    def _create_signal_combo_box(self):
        signal_combo_box = QComboBox()
        for s in self._signals:
            signal_combo_box.addItem(s.name())

        signal_combo_box.currentIndexChanged.connect(self._on_signal_combo_box_index_changed)
        return signal_combo_box

    @Slot()
    def _on_signal_combo_box_index_changed(self):
        signal = self.signal()

        self._parameter_spin_boxes.clear()
        while self._signal_parameter_layout.count() > 0:
            self._signal_parameter_layout.removeRow(0)

        for name in signal.parameter_names():
            spin_box = QDoubleSpinBox()
            spin_box.setMaximum(1000)
            spin_box.setValue(signal.parameter_value(name))
            spin_box.valueChanged.connect(self._on_parameter_spin_box_value_changed)

            self._signal_parameter_layout.addRow(name, spin_box)
            self._parameter_spin_boxes.append(spin_box)

        self.signalChanged.emit()

    @Slot()
    def _on_parameter_spin_box_value_changed(self):
        signal = self.signal()

        for i in range(len(signal.parameter_names())):
            signal.set_parameter_value(signal.parameter_names()[i], self._parameter_spin_boxes[i].value())

        self.signalChanged.emit()

    def signal(self):
        return self._signals[self._signal_combo_box.currentIndex()]

    def update(self, t, s):
        self._ax.cla()

        self._ax.plot(t, s, color='tab:orange')

        t, s = self.signal().signal()
        self._ax.plot(t, s, color='tab:blue')

        self._ax.set_xlabel('Time (s)')
        self._ax.set_ylabel('A')

        self._canvas.draw()
