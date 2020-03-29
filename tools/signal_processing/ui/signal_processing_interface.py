from PySide2.QtWidgets import QWidget, QTabWidget, QVBoxLayout

class SignalProcessingInterface(QWidget):
    def __init__(self, tabs):
        super().__init__()

        self._tabWidget = QTabWidget()

        for name, widget in tabs.items():
            self._tabWidget.addTab(widget, name)

        vlayout = QVBoxLayout()
        vlayout.addWidget(self._tabWidget)
        self.setLayout(vlayout)

