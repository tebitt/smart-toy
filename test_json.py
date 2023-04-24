import json
import serial
import time

ard = serial.Serial('/dev/cu.usbmodem12401',9600)

with open("data.json", "r") as f:
    data = json.load(f)
    f.close

parts = {}
for items in data:
    for ids in items['id']:
        parts[ids] = {'name': items['name'], 'score': items['score'] }

while True:
    ard_data = ard.readline()
    a = ard_data.decode("utf-8").replace('\r\n',"")
    print(a, parts[a])
    time.sleep(1)