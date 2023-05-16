import json
import serial
import time

veg_reader = '/dev/cu.usbmodem12401'
protein_reader = '/dev/cu.usbmodem12401'
fat_reader = '/dev/cu.usbmodem12401'
carbo_reader = '/dev/cu.usbmodem12401'
last_id = []
ard_ports = [veg_reader, protein_reader, fat_reader, carbo_reader]
baud_rate = 9600

ard = []
for port in ard_ports:
    try:
        connetion = serial.Serial(port, baud_rate)
        ard.append(connetion)
    except serial.SerialException:
        print(f"Count not connect to Arduino on port {port}")

reader_config = [{'validation':'veg'}, {'validation':'protein'}, {'validation':'fat'}, {'validation':'carbo'}]

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
    if(check_in_plate(id) == False):
        parts[id]['in_plate'] = True
        parts[parts[id]['counterpart']]['in_plate'] = True
        count[parts[id]['type']] += 1

def remove(id):
    if (id == []):
        return
    i = id[len(id) - 1]
    parts[i]['in_plate'] = False
    parts[parts[i]['counterpart']]['in_plate'] = False
    count[parts[i]['type']] -= 1
    #screen color goes back by 1 stage (amount? maybe? as in 0 is white 1 is yellow 2 is orange and 3 is green, >3 is red)

def reset():
    for i in parts: parts[i]['in_plate'] = False
    for i in count: count[i] = 0

while True:
    #if button pressed: reset()
    #if remove presed: remove(last_id) last_id.pop(-1)
    for i, connection in enumerate(ard):
        tag = connection.readline().decode("utf-8").replace('\r\n',"")
        print(tag)
        if parts[tag]['type'] in reader_config[i]['validation']:
            put_in_plate(tag)
            if(count[tag]['type'] > 3): pass
            #make screen red
            else: pass
            #make screen appropriate color yellow/orange/green
            print("Screen turned white/yellow/green/red depends on amount.")
            last_id.append(tag)
        else:
            print("Screen turned red.")
            pass
            #screen wrong food type (maybe other color than red to prevent confusion)
    time.sleep(0.1)