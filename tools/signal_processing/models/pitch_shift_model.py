import numpy as np
from scipy.signal.windows import hann

FRAME_SIZE = 1024
HOP_SIZE_IN = 256
GAIN_BY_PITCH_STEP = {
    -6: 1.2415331892552723,
    -5: 1.241652712452141,
    -4: 1.244615780432574,
    -3: 1.2585542092522932,
    -2: 1.2734288784043912,
    -1: 1.3001193733644227,
    0: 1.3333333333332817,
    1: 1.3758581127821765,
    2: 1.4344999204123041,
    3: 1.5157718389755686,
    4: 1.6224343855655563,
    5: 1.7459885206225656,
    6: 1.9106411955407752,
}


# Based on https://www.guitarpitchshifter.com/matlab.html
class PitchShiftModel:
    def __init__(self, configuration):
        self._configuration = configuration

        self._pitch_step = 0

    def pitch_step_ranges(self):
        return {'minValue': -6, 'maxValue': 6, 'resolution': 1}

    def update(self, pitch_step):
        self._pitch_step = pitch_step

    def process_audio(self, x):
        assert FRAME_SIZE / HOP_SIZE_IN == 4, "Only 75% overlap is supported."

        alpha = 2 ** (self._pitch_step / 12)
        hop_size_out = round(alpha * HOP_SIZE_IN)

        input_frames = self._create_non_overlapping_frames(x)
        window = hann(FRAME_SIZE)
        input_window = window / np.sqrt(FRAME_SIZE / HOP_SIZE_IN / 2)
        output_window = window / np.sqrt(FRAME_SIZE / hop_size_out / 2)

        previous_phase = np.zeros(FRAME_SIZE // 2 + 1)
        phase_cumulative = np.zeros(FRAME_SIZE // 2 + 1)

        input_processing_frame = np.zeros(FRAME_SIZE * 7 // 4)
        output_processing_frame = np.zeros(3 * hop_size_out + FRAME_SIZE)

        output_frames = []
        for input_frame in input_frames:
            input_processing_frame[-FRAME_SIZE:] = input_frame

            input_processing_frame_1 = input_processing_frame[:FRAME_SIZE]
            input_processing_frame_2 = input_processing_frame[HOP_SIZE_IN:HOP_SIZE_IN + FRAME_SIZE]
            input_processing_frame_3 = input_processing_frame[2 * HOP_SIZE_IN:2 * HOP_SIZE_IN + FRAME_SIZE]
            input_processing_frame_4 = input_processing_frame[3 * HOP_SIZE_IN:3 * HOP_SIZE_IN + FRAME_SIZE]

            output_processing_frame_1, previous_phase, phase_cumulative = self._process_frame(input_processing_frame_1,
                                                                                              previous_phase,
                                                                                              phase_cumulative,
                                                                                              input_window,
                                                                                              output_window,
                                                                                              hop_size_out)
            output_processing_frame_2, previous_phase, phase_cumulative = self._process_frame(input_processing_frame_2,
                                                                                              previous_phase,
                                                                                              phase_cumulative,
                                                                                              input_window,
                                                                                              output_window,
                                                                                              hop_size_out)
            output_processing_frame_3, previous_phase, phase_cumulative = self._process_frame(input_processing_frame_3,
                                                                                              previous_phase,
                                                                                              phase_cumulative,
                                                                                              input_window,
                                                                                              output_window,
                                                                                              hop_size_out)
            output_processing_frame_4, previous_phase, phase_cumulative = self._process_frame(input_processing_frame_4,
                                                                                              previous_phase,
                                                                                              phase_cumulative,
                                                                                              input_window,
                                                                                              output_window,
                                                                                              hop_size_out)

            output_processing_frame[:FRAME_SIZE] += output_processing_frame_1
            output_processing_frame[hop_size_out:hop_size_out + FRAME_SIZE] += output_processing_frame_2
            output_processing_frame[2 * hop_size_out:2 * hop_size_out + FRAME_SIZE] += output_processing_frame_3
            output_processing_frame[3 * hop_size_out:3 * hop_size_out + FRAME_SIZE] += output_processing_frame_4

            output_frames.append(self._resample_output_frame(output_processing_frame[:4 * hop_size_out], alpha))

            input_processing_frame[:3 * HOP_SIZE_IN] = input_processing_frame[FRAME_SIZE:FRAME_SIZE + 3 * HOP_SIZE_IN]
            input_processing_frame[3 * HOP_SIZE_IN:] = 0

            r = output_processing_frame[4 * hop_size_out:]
            output_processing_frame[:r.shape[0]] = r
            output_processing_frame[r.shape[0]:] = 0

        y = np.concatenate(output_frames)
        if y.shape[0] > x.shape[0]:
            y = y[:x.shape[0]]
        elif y.shape[0] < x.shape[0]:
            y = np.concatenate([y, np.zeros(x.shape[0] - y.shape[0])])
        return y * GAIN_BY_PITCH_STEP[int(self._pitch_step)]

    def _process_frame(self, input_frame, previous_phase, phase_cumulative, input_window, output_window, hop_size_out):
        X = np.fft.rfft(input_window * input_frame)
        magnitude = np.abs(X)
        phase = np.angle(X)

        delta_phi = phase - previous_phase
        previous_phase = phase

        ramp = np.linspace(0, np.pi, FRAME_SIZE // 2 + 1)
        delta_phi_prime = delta_phi - HOP_SIZE_IN * ramp
        delta_phi_prime_mod = np.remainder(delta_phi_prime + np.pi, 2 * np.pi) - np.pi

        true_freq = ramp + delta_phi_prime_mod / HOP_SIZE_IN
        phase_cumulative += hop_size_out * true_freq
        phase_cumulative = np.remainder(phase_cumulative + np.pi, 2 * np.pi) - np.pi

        output_frame = np.fft.irfft(magnitude * np.exp(1j * phase_cumulative)) * output_window
        return output_frame, previous_phase, phase_cumulative

    def _resample_output_frame(self, output_frame, alpha):
        t_in = np.arange(0, output_frame.shape[0], 1.0)
        t_out = np.arange(0, output_frame.shape[0], alpha)
        return np.interp(t_out, t_in, output_frame)

    def _create_non_overlapping_frames(self, x):
        count = x.shape[0] // FRAME_SIZE

        frames = []
        for i in range(count):
            start = i * FRAME_SIZE
            end = start + FRAME_SIZE
            frames.append(x[start:end])

        return frames
