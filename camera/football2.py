import sensor, image, time
from pyb import UART
import json
import gc

# Инициализация UART
uart = UART(3, 115200)
uart.init(115200, bits=8, parity=None, stop=0)


def CamSetup():
    import sensor, time

    # Сброс
    sensor.reset()

    # Настройка размера буфера ДО других настроек
    sensor.set_framesize(sensor.QQVGA80)  # 160x120 или 320x240
    sensor.set_pixformat(sensor.RGB565)

    # Установка буфера кадров (попробуйте 2 или 3)
    sensor.set_framebuffers(2)  # Изменено с 1 на 2

    # Ручные настройки
    sensor.set_auto_exposure(False)
    sensor.set_auto_whitebal(False)
    sensor.set_auto_gain(False)  # Если проблема - закомментируйте

    sensor.set_exposure_us(15000)
    sensor.set_gainceiling(8)
    sensor.set_brightness(0)
    sensor.set_contrast(0)
    sensor.set_saturation(0)

    # ВАЖНО: пропустить кадры для стабилизации
    for i in range(50):  # Пропускаем 50 кадров
        sensor.snapshot()
        time.sleep_ms(10)

    gc.collect()

    print("Camera manual mode initialized")
    print("Resolution: {}x{}".format(sensor.width(), sensor.height()))


def GetGates():
    green_threshold = (0, 0, 0, 0, 0, 0)  # ЗАМЕНИТЕ на реальные значения!

    try:
        # Ищем пятна зеленого цвета
        blobs = img.find_blobs([green_threshold], pixels_threshold=100,
                               area_threshold=100, merge=True, margin=10)

        if blobs:
            blobs.sort(key=lambda b: b.area(), reverse=True)
            gate = blobs[0]
            gate_center_x = gate.cx()
            CamError = getError(gate_center_x)
            SendMessage(CamError)
    except Exception as e:
        print("Error in GetGates:", e)


def getError(gate_center_x):
    CamError = gate_center_x - (sensor.width() // 2)

    # Для отладки
    print("CamError: {}".format(CamError))

    return CamError


def SendMessage(CamError):
    # Формируем сообщение
    #message = "CAM_ERROR:{}\n".format(CamError)
    message = CamError

    # Отправляем через UART
    #uart.write(message)
    uart.writechar(message)

    # Для отладки
    print("Sent: {}".format(message.strip()))


def test_connection():
    data = 0
    while data != b'\xff':
        uart.write(b'\xff')
        data = uart.read()
        print(data)
    print("Test connection succeed")


test_connection()
# Основной цикл
while True:
    img = sensor.snapshot()
    GetGates()
    time.sleep_ms(50)
