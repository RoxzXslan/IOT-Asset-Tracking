import requests

node_ip = ["192.168.178.206","192.168.178.68"]

api_key = '5X5BHVRWVIBYE514'

status = {node_ip[0]:'Inactive', node_ip[1]:'Inactive'}

def post(status, ip):
    data = {
        'api_key': api_key,
        'field1': status[ip[0]],
        'field2': status[ip[1]]
    }

    response = requests.post('https://api.thingspeak.com/update',params=data)

    if response.status_code == 200:
        print("sent")
    else:
        print("oops")

try:
    while(True):
        for ip in node_ip:
            try:
                response = requests.get(f"http://{ip}/status", timeout=1.5)
                status[ip] = 'Active'
            except requests.ConnectionError:
                status[ip] = 'Inactive'
        post(status, node_ip)
        print(status)
except KeyboardInterrupt:
    print("Exiting...")