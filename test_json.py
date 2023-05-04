import json
import serial
import time

ard = serial.Serial('/dev/cu.usbmodem12401',9600)

with open("data.json", "r") as f:
    data = json.load(f)
    f.close

parts = {}
for items in data:
    parts[items['id'][0]] = {'name': items['name'], 'in_plate': items['in_plate'], 'counter_part': items['id'][1]}
    parts[items['id'][1]] = {'name': items['name'], 'in_plate': items['in_plate'], 'counter_part': items['id'][0]}

for i in parts:
    print(i, parts[i])

while True:
    ard_data = ard.readline()
    a = ard_data.decode("utf-8").replace('\r\n',"")
    print(a, parts[a])
    time.sleep(1)