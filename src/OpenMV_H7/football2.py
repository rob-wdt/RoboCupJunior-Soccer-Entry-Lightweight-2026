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
                draw(_img, "RECTANGLE", i.x(), i.y(),
                     i.x() + i.w(), i.y() + i.h())
    else:
        _gates_x = None

    return _gates_x


def to_borders(_val, _min, _max):
    if _val < _min:
        _val = _min
    elif _val > _max:
        _val = _max

    return _val


def protect_val(_val):
    if _val is not None:
        _val = to_borders(_val, 0, 254)
    else:
        _val = 255
    return _val


def send(_UART, _data):
    _UART.writechar(_data)
    print(f"Sent data:\t{_data}")


def test_connection(_UART, _val=0):
    while _val != b'\xff':
        _UART.writechar(255)
        _val = _UART.read()
        print(_val)
    print("TEST CONNECTION SUCCEED")


def draw(_img, _what, _x_min, _y_min, _x_max, _y_max):
    if _what == "CROSS":
        _x = _x_min
        _y = _y_min
        _img.draw_cross(_x, _y, (0, 0, 0), size=10)
    elif _what == "RECTANGLE":
        _img.draw_rectangle(_x_min, _y_min, _x_max - _x_min,
                            _y_max - _y_min, (0, 0, 0))


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
test_connection(uart)

while True:
    img = sensor.snapshot()
    draw(img, "CROSS", CAM_CENTER[0],
         CAM_CENTER[1], CAM_CENTER[0], CAM_CENTER[1])

    if GATES == "BLUE":
        gates_x = find_gates(img, BLUE_THRESHOLD)
    elif GATES == "YELLOW":
        gates_x = find_gates(img, YELLOW_THRESHOLD)

    gates_x = protect_val(gates_x)
    error = gates_x
    if gates_x < 255:
        error -= CAM_CENTER[0]
    # print(error)

    send(uart, error)
