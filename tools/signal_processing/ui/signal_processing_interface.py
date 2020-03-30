import numpy as np
import scipy.io.wavfile
import sounddevice as sd

from PySide2.QtCore import Slot
from PySide2.QtWidgets import QWidget, QTabWidget, QHBoxLayout, QVBoxLayout, QLabel, QLineEdit, QPushButton, QFileDialog


class SignalProcessingInterface(QWidget):
    def __init__(self, tabs):
        super().__init__()
        self._tabWidgets = list(tabs.values())

        self._tabWidget = QTabWidget()

        for name, widget in tabs.items():
            self._tabWidget.addTab(widget, name)

        wav_label = QLabel('Wav :')
        self._wav_line_edit = QLineEdit()
        self._wav_line_edit.setReadOnly(True)

        self._wav_browse_button = QPushButton('Browse')
        self._wav_browse_button.setMaximumWidth(100)
        self._wav_play_button = QPushButton('Play')
        self._wav_play_button.setMaximumWidth(100)

        hlayout = QHBoxLayout()
        hlayout.addWidget(wav_label)
        hlayout.addWidget(self._wav_line_edit)
        hlayout.addWidget(self._wav_browse_button)
        hlayout.addWidget(self._wav_play_button)

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._tabWidget)
        vlayout.addLayout(hlayout)
        self.setLayout(vlayout)

        self._wav_browse_button.clicked.connect(self._on_wav_browse_button_clicked)
        self._wav_play_button.clicked.connect(self._on_wav_play_button_clicked)

    @Slot()
    def _on_wav_browse_button_clicked(self):
        wav_file, _ = QFileDialog.getOpenFileName(self, 'Select a WAV file', '', 'WAV File (*.wav)')
        self._wav_line_edit.setText(wav_file)

    @Slot()
    def _on_wav_play_button_clicked(self):
        fs, x = scipy.io.wavfile.read(self._wav_line_edit.text())
        x = x.astype(float)
        x /= np.abs(x).max()

        model = self._tabWidgets[self._tabWidget.currentIndex()].model()
        y = model.process_audio(x)

        sd.stop()
        sd.play(y, fs)
