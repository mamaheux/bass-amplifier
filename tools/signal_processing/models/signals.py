import numpy as np

class BaseSignal:
    def __init__(self, name, parameter_names, fs):
        self._name = name
        self._parameter_names = parameter_names
        self._parameter_values = {}
        self._fs = fs

        for name in self._parameter_names:
            self._parameter_values[name] = 0.0

    def name(self):
        return self._name

    def parameter_names(self):
        return self._parameter_names

    def parameter_value(self, name):
        return self._parameter_values[name]

    def set_parameter_value(self, name, value):
        self._parameter_values[name] = value


class StepSignal(BaseSignal):
    def __init__(self, fs):
        super().__init__('Step', ['A', 'T_1', 'T_2', 'T_3'], fs)
        self.set_parameter_value('A', 1)
        self.set_parameter_value('T_1', 0.3)
        self.set_parameter_value('T_2', 0.3)
        self.set_parameter_value('T_3', 0.3)

    def signal(self):
        A = self.parameter_value('A')
        T_1 = self.parameter_value('T_1')
        T_2 = self.parameter_value('T_2')
        T_3 = self.parameter_value('T_3')

        dt = 1 / self._fs
        t = np.arange(0, T_1 + T_2 + T_3, dt)

        s1 = np.zeros(int(T_1 / dt))
        s2 = A * np.ones(int(T_2 / dt))
        s3 = np.zeros(int(T_3 / dt))

        s = np.concatenate((s1, s2, s3))

        if s.shape[0] < t.shape[0]:
            s = np.concatenate((s, np.zeros(t.shape[0] - s.shape[0])))

        return t, s


class SinSignal(BaseSignal):
    def __init__(self, fs):
        super().__init__('Sin', ['A', 'F', 'T'], fs)
        self.set_parameter_value('A', 1)
        self.set_parameter_value('F', 100)
        self.set_parameter_value('T', 0.1)

    def signal(self):
        A = self.parameter_value('A')
        F = self.parameter_value('F')
        T = self.parameter_value('T')

        dt = 1 / self._fs
        t = np.arange(0, T, dt)

        s = A * np.sin(2 * np.pi * F * t)

        return t, s


class SinStepSignal(BaseSignal):
    def __init__(self, fs):
        super().__init__('Sin + Step', ['A_step', 'T_1', 'T_2', 'T_3', 'A_sin', 'F_sin'], fs)
        self.set_parameter_value('A_step', 1)
        self.set_parameter_value('T_1', 0.03)
        self.set_parameter_value('T_2', 0.03)
        self.set_parameter_value('T_3', 0.03)
        self.set_parameter_value('A_sin', 0.2)
        self.set_parameter_value('F_sin', 100)

    def signal(self):
        A_step = self.parameter_value('A_step')
        T_1 = self.parameter_value('T_1')
        T_2 = self.parameter_value('T_2')
        T_3 = self.parameter_value('T_3')
        A_sin = self.parameter_value('A_sin')
        F_sin = self.parameter_value('F_sin')

        dt = 1 / self._fs
        t = np.arange(0, T_1 + T_2 + T_3, dt)

        s1 = np.zeros(int(T_1 / dt))
        s2 = A_step * np.ones(int(T_2 / dt))
        s3 = np.zeros(int(T_3 / dt))

        s_step = np.concatenate((s1, s2, s3))

        if s_step.shape[0] < t.shape[0]:
            s_step = np.concatenate((s_step, np.zeros(t.shape[0] - s_step.shape[0])))

        s_sin = A_sin * np.sin(2 * np.pi * F_sin * t)

        return t, s_step + s_sin

class LinearSignal(BaseSignal):
    def __init__(self, fs):
        super().__init__('Linear', ['T_0', 'A_0', 'T_1', 'A_1'], fs)
        self.set_parameter_value('T_0', 0)
        self.set_parameter_value('A_0', -1)
        self.set_parameter_value('T_1', 1)
        self.set_parameter_value('A_1', 1)

    def signal(self):
        T_0 = self.parameter_value('T_0')
        A_0 = self.parameter_value('A_0')
        T_1 = self.parameter_value('T_1')
        A_1 = self.parameter_value('A_1')

        dt = 1 / self._fs
        t = np.arange(T_0, T_1, dt)
        s = np.interp(t, [T_0, T_1], [A_0, A_1])

        return t, s


class SinModSignal(BaseSignal):
    def __init__(self, fs):
        super().__init__('Sin*Step', ['A_0', 'A_1', 'F', 'T_1', 'T_2', 'T_3'], fs)
        self.set_parameter_value('A_0', 0.1)
        self.set_parameter_value('A_1', 1)
        self.set_parameter_value('F', 100)
        self.set_parameter_value('T_1', 0.03)
        self.set_parameter_value('T_2', 0.03)
        self.set_parameter_value('T_3', 0.03)

    def signal(self):
        A_0 = self.parameter_value('A_0')
        A_1 = self.parameter_value('A_1')
        F = self.parameter_value('F')
        T_1 = self.parameter_value('T_1')
        T_2 = self.parameter_value('T_2')
        T_3 = self.parameter_value('T_3')

        dt = 1 / self._fs
        t = np.arange(0, T_1 + T_2 + T_3, dt)

        s1 = A_0 * np.ones(int(T_1 / dt))
        s2 = A_1 * np.ones(int(T_2 / dt))
        s3 = A_0 * np.ones(int(T_3 / dt))

        s_step = np.concatenate((s1, s2, s3))

        if s_step.shape[0] < t.shape[0]:
            s_step = np.concatenate((s_step, np.zeros(t.shape[0] - s_step.shape[0])))

        s_sin = np.sin(2 * np.pi * F * t)

        return t, s_step * s_sin
