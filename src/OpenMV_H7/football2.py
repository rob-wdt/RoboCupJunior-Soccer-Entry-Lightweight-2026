import sensor
import pyb


# --------------------FUNCTIONS-----------------------

def setup_sensor(_pixformat, _framesize, _gain, _whitebal, _exposure, frame_width, frame_height):
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

    sensor.set_windowing((frame_width, frame_height))

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
                _x = i.x()
                _y = i.y()
                _w = i.w()
                _h = i.h()

        # Draw rectangle
        draw(_img, "RECTANGLE", _x, _y,
             _x + _w, _y + _h)
    else:
        _gates_x = None

    return _gates_x


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
GATES = "YELLOW"

PIXFORMAT = sensor.RGB565
FRAMESIZE = sensor.QVGA
GAIN = 10
WHITE = (-3, -4, -1)
EXPOSURE = 7_000

if FRAMESIZE == sensor.QVGA:
    FRAME_WIDTH = 320
FRAME_HEIGHT = 60

YELLOW_THRESHOLD = [(50, 100, -29, 96, 45, 127)]
BLUE_THRESHOLD = [(0, 70, -40, 0, -50, -10)]

CAM_CENTER = (sensor.width() // 2, sensor.height() // 2)

# ---------------------VARIABLES----------------------
uart = pyb.UART(3, 230400)
# TX - P4, RX - P5


# -----------------------MAIN CODE-----------------------
setup_sensor(PIXFORMAT, FRAMESIZE, GAIN, WHITE, EXPOSURE, FRAME_WIDTH, FRAME_HEIGHT)
# test_connection(uart)

while True:
    img = sensor.snapshot()
    draw(img, "CROSS", CAM_CENTER[0],
         CAM_CENTER[1], CAM_CENTER[0], CAM_CENTER[1])

    if GATES == "BLUE":
        gates_x = find_gates(img, BLUE_THRESHOLD)
    elif GATES == "YELLOW":
        gates_x = find_gates(img, YELLOW_THRESHOLD)

    if gates_x is None:
        send(uart, 0)
        continue
    elif gates_x is not None:
        error = 1 * (gates_x - CAM_CENTER[0])
        if error < -127:
            error = -127
        elif error > 127:
            error = 127

        send(uart, error)
