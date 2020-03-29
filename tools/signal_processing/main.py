import sys

from PySide2.QtWidgets import QApplication

from configuration import Configuration

from ui.signal_processing_interface import SignalProcessingInterface
from ui.effects.compressor_widget import CompressorWidget

from models.compressor_model import CompressorModel

def main():
    configuration = Configuration(fs=48000)

    app = QApplication(sys.argv)
    interface = SignalProcessingInterface()
    interface.show()


    a = CompressorWidget(configuration, CompressorModel(configuration))
    a.show()

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
