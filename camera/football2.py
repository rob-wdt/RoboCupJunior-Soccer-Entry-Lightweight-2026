import sensor, image, time
from pyb import UART
import json

# Инициализация UART
uart = UART(1, 115200)
uart.init(115200, bits=8, parity=None, stop=1)


def CamSetup():
    import sensor, time

    # Сброс и базовая настройка
    sensor.reset()
    sensor.set_pixformat(sensor.RGB565)
    sensor.set_framesize(sensor.QVGA)  # 320x240

    # Ручные настройки для стабильного изображения
    sensor.set_auto_exposure(False)
    sensor.set_auto_whitebal(False)
    sensor.set_auto_gain(False)

    sensor.set_exposure_us(15000)
    sensor.set_gainceiling(8)
    sensor.set_brightness(0)  # яркость
    sensor.set_contrast(0)  # контраст
    sensor.set_saturation(0)  # Насыщенность

    # sensor.set_rgb_gain(1.0, 1.0, 1.0)  #опционально ргб коэффициенты

    # время на стабилизацию
    time.sleep_ms(500)

    print("Camera manual mode initialized")
    print("Resolution: {}x{}".format(sensor.width(), sensor.height()))


def GetGates():
    green_threshold = (0, 0, 0, 0, 0, 0)  # (R_min, R_max, G_min, G_max, B_min, B_max)

    # Ищем пятна зеленого цвета
    blobs = img.find_blobs([green_threshold], pixels_threshold=100, area_threshold=100, merge=True, margin=10)

    if blobs:
        # Сортируем по площади и берем самый большой
        blobs.sort(key=lambda b: b.area(), reverse=True)
        gate = blobs[0]

        # Характеристики ворот
        gate_center_x = gate.cx()

        # Функция ошибки
        getError(gate_center_x)

        # Отправляем ошибку в другую программу
        SendMessage(CamError)


def getError(gate_center_x):
    CamError = gate_center_x - (sensor.width() // 2)

    # Для отладки
    print("CamError: {}".format(CamError))

    return CamError


def SendMessage(CamError):
    # Формируем сообщение
    message = "CAM_ERROR:{}\n".format(CamError)

    # Отправляем через UART
    uart.write(message)

    # Для отладки
    print("Sent: {}".format(message.strip()))


def test_connection():
    val = 0
    while val != 1:
        val = uart.read(1)
    uart.write(1)


test_connection()
# Основной цикл
while True:
    img = sensor.snapshot()
    GetGates()
    time.sleep_ms(50)
