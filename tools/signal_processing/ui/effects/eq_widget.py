from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QVBoxLayout, QHBoxLayout, QGroupBox

from ui.utils.double_slider import DoubleSlider
from ui.utils.gain_plot_widget import GainPlotWidget

class EqWidget(QWidget):
    def __init__(self, configuration):
        super().__init__()
        self._configuration = configuration
        self._create_ui()

        self._low_freq_slider.set_value(100)
        self._low_mid_freq_slider.set_value(250)
        self._high_mid_freq_slider.set_value(1000)
        self._high_freq_slider.set_value(2500)

    def _create_ui(self):
        self._low_group_box = QGroupBox('Low')
        self._low_gain_slider = DoubleSlider('Gain (dB)', minValue=0, maxValue=5, resolution=0.1)
        self._low_freq_slider = DoubleSlider('Freq (Hz)', minValue=10, maxValue=self._configuration.fs // 200,
                                             resolution=10)
        self._low_q_slider = DoubleSlider('Q', minValue=0, maxValue=5, resolution=0.1)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._low_gain_slider)
        hlayout.addWidget(self._low_freq_slider)
        hlayout.addWidget(self._low_q_slider)
        self._low_group_box.setLayout(hlayout)

        self._low_mid_group_box = QGroupBox('Low mid')
        self._low_mid_gain_slider = DoubleSlider('Gain (dB)', minValue=0, maxValue=5, resolution=0.1)
        self._low_mid_freq_slider = DoubleSlider('Freq (Hz)', minValue=self._configuration.fs // 400,
                                                 maxValue=self._configuration.fs // 100, resolution=10)
        self._low_mid_q_slider = DoubleSlider('Q', minValue=0, maxValue=5, resolution=0.1)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._low_mid_gain_slider)
        hlayout.addWidget(self._low_mid_freq_slider)
        hlayout.addWidget(self._low_mid_q_slider)
        self._low_mid_group_box.setLayout(hlayout)

        self._high_mid_group_box = QGroupBox('High mid')
        self._high_mid_gain_slider = DoubleSlider('Gain (dB)', minValue=0, maxValue=5, resolution=0.1)
        self._high_mid_freq_slider = DoubleSlider('Freq (Hz)', minValue=self._configuration.fs // 200,
                                                  maxValue=self._configuration.fs // 20, resolution=10)
        self._high_mid_q_slider = DoubleSlider('Q', minValue=0, maxValue=5, resolution=0.1)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._high_mid_gain_slider)
        hlayout.addWidget(self._high_mid_freq_slider)
        hlayout.addWidget(self._high_mid_q_slider)
        self._high_mid_group_box.setLayout(hlayout)

        self._high_group_box = QGroupBox('High')
        self._high_gain_slider = DoubleSlider('Gain (dB)', minValue=0, maxValue=5, resolution=0.1)
        self._high_freq_slider = DoubleSlider('Freq (Hz)', minValue=self._configuration.fs // 20,
                                              maxValue=self._configuration.fs // 2, resolution=10)
        self._high_q_slider = DoubleSlider('Q', minValue=0, maxValue=5, resolution=0.1)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._high_gain_slider)
        hlayout.addWidget(self._high_freq_slider)
        hlayout.addWidget(self._high_q_slider)
        self._high_group_box.setLayout(hlayout)

        hlayout = QHBoxLayout()
        hlayout.addWidget(self._low_group_box)
        hlayout.addWidget(self._low_mid_group_box)
        hlayout.addWidget(self._high_mid_group_box)
        hlayout.addWidget(self._high_group_box)
        hlayout.addStretch()

        self._plot = GainPlotWidget(max_frequency=self._configuration.fs // 2)

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._plot)
        vlayout.addLayout(hlayout)
        self.setLayout(vlayout)





