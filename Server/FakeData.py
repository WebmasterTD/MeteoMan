import json
from datetime import datetime, timedelta
import random

if __name__ == '__main__':
    current_ts = datetime.now()
    delta = timedelta(minutes = 10)

    data = list()

    current_ts += delta
    temp = random.uniform(10, 30.0)
    humid = random.uniform(40, 60.0)
    rain = random.uniform(0.0, 5.0)

    for i in range(100):
        ts = current_ts + (i * delta)
        temp += random.uniform(-2, 2.0)
        humid += random.uniform(-5, 5.0)
        rain = random.uniform(0.0, 1.0)

        row = [ts.strftime('%Y-%m-%d %H:%M:%S'), temp, humid, rain]

        data.append(row)

json_data = json.dumps(data)
print(json_data)