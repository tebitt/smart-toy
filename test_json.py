import json
import serial
import time

veg_reader = '/dev/cu.usbmodem12401',
protein_reader = '/dev/cu.usbmodem12401',
fat_reader = '/dev/cu.usbmodem12401',
carbo_reader = '/dev/cu.usbmodem12401'
ard_ports = [veg_reader, protein_reader, fat_reader, carbo_reader]
baud_rate = 9600

ard = []
for port in ard_ports:
    try:
        connetion = serial.Serial(port, baud_rate, timeout = 1)
        ard.append(connetion)
    except serial.SerialException:
        print(f"Count not connect to Arduino on port {port}")

reader_config = [
    {'validation':'veg'},
    {'validation':'protein'},
    {'validation':'fat'},
    {'validation':'carbo'},
]

with open("data.json", "r") as f:
    data = json.load(f)
    f.close

parts = {}
count = {'veg':0, 'fat':0, 'protein':0, 'carbo':0}

for items in data:
    parts[items['id'][0]] = {'name': items['name'], 'type':items['type'], 'in_plate': False, 'counterpart': items['id'][1]}
    parts[items['id'][1]] = {'name': items['name'], 'type':items['type'], 'in_plate': False, 'counterpart': items['id'][0]}

def check_in_plate(id):
    if(parts[id]['in_plate'] or parts[parts[id]['counterpart']]['in_plate']): return True
    else: return False

def put_in_plate(id):
    if(check_in_plate(id) == False and count[parts[id]['type']] < 3):
        parts[id]['in_plate'] = True
        parts[parts[id]['counterpart']]['in_plate'] = True
        count[parts[id]['type']] += 1

def reset():
    for i in parts: parts[i]['in_plate'] = False
    for i in count: count[i] = 0

while True:
    #if button pressed: reset()
    ard_data = ard.readline()
    a = ard_data.decode("utf-8").replace('\r\n',"")
    put_in_plate(a)
    #screen
    time.sleep(1)
