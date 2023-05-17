import serial
import time

port = '/dev/cu.usbmodem12101'
screen = serial.Serial(port, 9600)

def write(x):
    x = str(x)
    screen.write(bytes(x, 'utf-8'))
    time.sleep(0.1)
    return

write(1) ## fat / white 100
write(2) ## fat / green 101
write(3) ## fat / red   102
write(4) ## protein / white 200
write(5) ## protein / yellow 201
write(6) ## protein / green 202
write(7) ## protein / red 203
write(8) ## vitamin / white 300
write(9) ## vitamin / yellow 301
write(10) ## vitamin / yellowgreen 302
write(11) ## vitamin / green 303
write(12) ## vitamin / red 304
write(13) ## carbohydrate / white 400
write(14) ## carbohydrate / bright yellow 401
write(15) ## carbohydrate / yellow 402
write(16) ## carbohydrate / yellow green 403
write(17) ## carbohydrate / green 404
write(18) ## carbohydrate / red 405
write(19) ## restart (every portion = white) 000