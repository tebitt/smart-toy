import json
import serial
import time

veg_reader = '/dev/cu.usbmodem12401'
protein_reader = '/dev/cu.usbmodem12301'
fat_reader = '/dev/cu.usbmodem12101'
carbo_reader = '/dev/cu.usbmodem11201'
monitor = '/dev/cu.usbmodem11401'
last_id = []
ard_ports = [veg_reader, protein_reader, fat_reader, carbo_reader]
baud_rate = 9600

monitor_connection = serial.Serial(monitor, baud_rate)
ard = []
for port in ard_ports:
    try:
        connetion = serial.Serial(port, baud_rate)
        ard.append(connetion)
    except serial.SerialException:
        print(f"Count not connect to Arduino on port {port}")

reader_config = [{'validation':'veg'}, {'validation':'protein'}, {'validation':'fat'}, {'validation':'carbo'}]
M = {'veg':3, 'fat':1, 'protein':2, 'carbo':4}

with open("data.json", "r") as f:
    data = json.load(f)
    f.close

parts = {}
count = {'veg':0, 'fat':0, 'protein':0, 'carbo':0} #3124

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
    id.pop(-1)
    #screen color goes back by 1 stage (amount? maybe? as in 0 is white 1 is yellow 2 is orange and 3 is green, >3 is red)

def reset():
    for i in parts: parts[i]['in_plate'] = False
    for i in count: count[i] = 0

while True:
    for i, connection in enumerate(ard):
        if connection.in_waiting > 0:
            tag = connection.readline().decode("utf-8").replace('\r\n',"")
            if tag == "RST": 
                reset()
                last_id = []
            elif tag == "RML": 
                remove(last_id)
            elif parts[tag]['type'] == reader_config[i]['validation']:
                put_in_plate(tag)
                if(count[parts[tag]['type']] > M[parts[tag]['type']]): pass
                #make screen red
                else: pass
                #make screen appropriate color yellow/orange/green
                print("Screen turned white/yellow/green/red depends on amount.", parts[tag]['type'], parts[tag]['name'])
                if(tag in last_id) or (parts[tag]['counterpart'] in last_id): pass
                else: last_id.append(tag)
            else:
                print("Screen turned red.")
            print(last_id, tag)
                #screen wrong food type (maybe other color than red to prevent confusion)
    time.sleep(1)