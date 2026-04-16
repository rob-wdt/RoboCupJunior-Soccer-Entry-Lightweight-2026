import sensor
import pyb

# -----------------------CONSTS--------------------
GATES = "YELLOW"

GAIN = 1
WHITE = (0, -3, 0)
EXPOSURE = 7_000

YELLOW_THRESHOLD = ()
BLUE_THRESHOLD = ()

CAM_CENTER = sensor.width() // 2

# ---------------------VARIABLES----------------------
uart = pyb.UART(3, 115200)


# --------------------FUNCTIONS-----------------------

def setup_sensor():
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QQVGA)
    sensor.set_auto_gain(True)
    sensor.set_auto_whitebal(True)
    sensor.set_auto_exposure(True)

    sensor.skip_frames(time=100)

    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QQVGA)
    sensor.set_auto_gain(False, gain_db=GAIN)
    sensor.set_auto_whitebal(False, rgb_gain_db=WHITE)
    sensor.set_auto_exposure(False, exposure_us=EXPOSURE)

    sensor.skip_frames(time=100)


def find_gates(_img, _threshold, _cam_center, _area=0, _prev_area=0):
    # Detecting yellow gates
    for i in _img.find_blobs(_threshold):
        _area = i[2] * i[3]
        if _area >= _prev_area:
            _prev_area = _area

            # Fill the error variable
            _error = i.cx() - _cam_center

    return _error


def protect_value(_val, _min, _max):
    if _val < _min:
        _val = _min
    elif _val > _max:
        _val = _max

    return _val


def send(_UART, _data):
    _data = protect_value(_data, 0, 255)
    _UART.writechar(_data)


# -----------------------MAIN CODE-----------------------
setup_sensor()

while True:
    img = sensor.snapshot()

    if GATES == "BLUE":
        error = find_gates(img, BLUE_THRESHOLD, CAM_CENTER)

    elif GATES == "YELLOW":
        error = find_gates(img, YELLOW_THRESHOLD, CAM_CENTER)

    # send(uart, error)
