import re
import matplotlib.pyplot as plt
from matplotlib.ticker import ScalarFormatter

file_path = './output/output_data.txt'

with open(file_path, 'r') as file:
    data = file.read()

pattern = re.compile(r'Binary - Attempts (\d+) - (\d+)')

matches = pattern.findall(data)

data = {}

for match in matches:
    attempt, ms = match

    data.setdefault(attempt, {'sum': 0, 'count': 0})
    data[attempt]['sum'] += int(ms)
    data[attempt]['count'] += 1


average_data = {int(attempt): (values['sum'] / values['count']) for attempt, values in data.items()}

for attempt, value in average_data.items():
    print(f"{str(attempt).rjust(12)}     val: {value:.3f}")

# Plotting
fig, ax = plt.subplots()

ax.plot(average_data.keys(), average_data.values(), marker='o', linestyle='-')
ax.set_xscale('log')
ax.set_yscale('log')
ax.set_xlabel('attempts')
ax.set_ylabel('ms')
ax.grid(True)
plt.show()