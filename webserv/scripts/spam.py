import threading
import requests

def run():
    for i in range(500):
        requests.get("http://localhost")
        
threads = []
for i in range(100):
    thread = threading.Thread(target=run)
    thread.start()
    
    threads.append(thread)

for thread in threads:
    thread.join()