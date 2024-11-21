import requests
import serial

api_key = 'AH2Z0NCNQRLUH3ZB'

def post(lat,lon):
    data = {
        'api_key': api_key,
        'field1': lat,
        'field2': lon
    }

    response = requests.post('https://api.thingspeak.com/update',params=data)

    if response.status_code == 200:
        print("sent")
    else:
        print("oops")

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()

    while True:
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            if line == 'Sim808 init error':
                print('init error')
            elif line == 'Open the GPS power success':
                print('module success')
            else:
                gps = line.split(',')
                lat = gps[0].split(":")[1]
                lon = gps[1].split(":")[1]
                post(lat,lon)
                print(f'{lat} {lon}')