import sys

from PySide2.QtWidgets import QApplication

from configuration import Configuration

from ui.signal_processing_interface import SignalProcessingInterface


from ui.effects.contour_widget import ContourWidget
from ui.effects.presence_widget import PresenceWidget
from ui.effects.eq_widget import EqWidget
from ui.effects.compressor_widget import CompressorWidget
from ui.effects.octaver_widget import OctaverWidget
from ui.effects.delay_widget import DelayWidget
from ui.effects.reverb_widget import ReverbWidget
from ui.effects.overdrive_widget import OverdriveWidget

from models.contour_model import ContourModel
from models.presence_model import PresenceModel
from models.eq_model import EqModel
from models.compressor_model import CompressorModel
from models.octaver_model import OctaverModel
from models.delay_model import DelayModel
from models.reverb_model import ReverbModel
from models.overdrive_model import OverdriveModel

def main():
    configuration = Configuration(fs=48000)

    app = QApplication(sys.argv)

    tabs = { 'Contour': ContourWidget(configuration, ContourModel(configuration)),
             'Presence': PresenceWidget(configuration, PresenceModel(configuration)),
             'EQ': EqWidget(configuration, EqModel(configuration)),
             'Compressor': CompressorWidget(configuration, CompressorModel(configuration)),
             'Octaver': OctaverWidget(configuration, OctaverModel(configuration)),
             'Delay': DelayWidget(configuration, DelayModel(configuration)),
             'Reverb': ReverbWidget(configuration, ReverbModel(configuration)),
             'Overdrive': OverdriveWidget(configuration, OverdriveModel(configuration))}

    interface = SignalProcessingInterface(tabs)
    interface.show()

    sys.exit(app.exec_())


if __name__ == "__main__":
    main()
