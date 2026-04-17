import sensor
import pyb


# --------------------FUNCTIONS-----------------------

def setup_sensor(_pixformat, _framesize, _gain, _whitebal, _exposure):
    sensor.reset()
    sensor.set_pixformat(_pixformat)
    sensor.set_framesize(_framesize)
    sensor.set_auto_gain(True)
    sensor.set_auto_whitebal(True)
    sensor.set_auto_exposure(True)

    sensor.skip_frames(time=100)

    sensor.set_pixformat(_pixformat)
    sensor.set_framesize(_framesize)
    sensor.set_auto_gain(False, gain_db=_gain)
    sensor.set_auto_whitebal(False, rgb_gain_db=_whitebal)
    sensor.set_auto_exposure(False, exposure_us=_exposure)

    sensor.skip_frames(time=100)


def find_gates(_img, _threshold, _area=0, _prev_area=0, _gates_x=0):
    _blobs = _img.find_blobs(_threshold)
    if len(_blobs):
        # Detecting gates
        for i in _img.find_blobs(_threshold):
            _area = i.h() * i.w()
            if _area >= _prev_area:
                _prev_area = _area

                # Get x coordinate of the gates
                _gates_x = i.cx()

                # Draw rectangle
                draw(_img, "RECTANGLE", i.x(), i.y(), i.x() + i.w(), i.y() + i.h())
    else:
        _gates_x = None

    return _gates_x


def to_borders(_val, _min, _max):
    if _val < _min:
        _val = _min
    elif _val > _max:
        _val = _max

    return _val


def send(_UART, _data):
    if _data is not None:
        _data = to_borders(_data, 0, 254)
    else:
        _data = 255

    _UART.writechar(_data)


def draw(_img, _what, _x_min, _y_min, _x_max, _y_max):
    if _what == "CROSS":
        _x = _x_min
        _y = _y_min
        _img.draw_cross(_x, _y, (0, 0, 0), size=10)
    elif _what == "RECTANGLE":
        _img.draw_rectangle(_x_min, _y_min, _x_max - _x_min, _y_max - _y_min, (0, 0, 0))


# -----------------------CONSTS--------------------
GATES = "BLUE"

PIXFORMAT = sensor.RGB565
FRAMESIZE = sensor.QVGA
GAIN = 1
WHITE = (-3, -3, 0)
EXPOSURE = 7_000

YELLOW_THRESHOLD = [(40, 75, -40, -15, 40, 90)]
BLUE_THRESHOLD = [(0, 70, -40, 0, -50, -10)]

CAM_CENTER = (sensor.width() // 2, sensor.height() // 2)

# ---------------------VARIABLES----------------------
uart = pyb.UART(3, 115200)
# TX - P4, RX - P5


# -----------------------MAIN CODE-----------------------
setup_sensor(PIXFORMAT, FRAMESIZE, GAIN, WHITE, EXPOSURE)

while True:
    img = sensor.snapshot()
    draw(img, "CROSS", CAM_CENTER[0], CAM_CENTER[1], CAM_CENTER[0], CAM_CENTER[1])

    if GATES == "BLUE":
        error = find_gates(img, BLUE_THRESHOLD) - CAM_CENTER[0]

    elif GATES == "YELLOW":
        error = find_gates(img, YELLOW_THRESHOLD) - CAM_CENTER[0]

    # send(uart, error)
