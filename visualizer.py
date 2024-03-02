import re
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import MultipleLocator

TEST_MULTITHREAD_DONE = True

par_bin_file = './output/output_data_parallel_binary_nthreads_12.txt'
seq_bin_file = './output/output_data_sequential_binary.txt'
par_str_file = './output/output_data_parallel_string_nthreads_12.txt'
seq_str_file = './output/output_data_sequential_string.txt'

with open(par_bin_file, 'r') as file:
    par_bin_data = file.read()

with open(seq_bin_file, 'r') as file:
    seq_bin_data = file.read()

with open(seq_str_file, 'r') as file:
    seq_str_data = file.read()

with open(par_str_file, 'r') as file:
    par_str_data = file.read()

bin_pattern = re.compile(r'Binary - Attempts (\d+) - (\d+)')
str_pattern = re.compile(r'String - Attempts (\d+) - (\d+)')

par_bin_matches = bin_pattern.findall(par_bin_data)
seq_bin_matches = bin_pattern.findall(seq_bin_data)
par_str_matches = str_pattern.findall(par_str_data)
seq_str_matches = str_pattern.findall(seq_str_data)

par_bin_data_list = [(int(attempts), int(value)) for attempts, value in par_bin_matches]
par_bin_norm_data_list = [(attempt, (value / attempt)) for attempt, value in par_bin_data_list]

seq_bin_data_list = [(int(attempts), int(value)) for attempts, value in seq_bin_matches]
seq_bin_norm_data_list = [(attempt, (value / attempt)) for attempt, value in seq_bin_data_list]

seq_str_data_list = [(int(attempts), int(value)) for attempts, value in seq_str_matches]
seq_str_norm_data_list = [(attempt, (value / attempt)) for attempt, value in seq_str_data_list]

par_str_data_list = [(int(attempts), int(value)) for attempts, value in par_str_matches]
par_str_norm_data_list = [(attempt, (value / attempt)) for attempt, value in par_str_data_list]

####################################################

# Processing parallel binary data
par_bin_data_dict = {}
for attempts, value in par_bin_data_list:
    if attempts not in par_bin_data_dict:
        par_bin_data_dict[attempts] = []
    par_bin_data_dict[attempts].append(value)

# Extracting data
par_bin_attempts_list = []
par_bin_means = []
par_bin_std_devs = []
for attempts, values in par_bin_data_dict.items():
    par_bin_attempts_list.append(attempts)
    par_bin_means.append(np.mean(values))
    par_bin_std_devs.append(np.std(values))

# Computing "normalized" data
par_bin_norm_data_dict = {}
for attempts, value in par_bin_norm_data_list:
    if attempts not in par_bin_norm_data_dict:
        par_bin_norm_data_dict[attempts] = []
    par_bin_norm_data_dict[attempts].append(value)

par_bin_norm_attempts_list = []
par_bin_norm_means = []
par_bin_norm_std_devs = []
for attempts, values in par_bin_norm_data_dict.items():
    par_bin_norm_attempts_list.append(attempts)
    par_bin_norm_means.append(np.mean(values))
    par_bin_norm_std_devs.append(np.std(values))

####################################################

# Processing sequential binary data
seq_bin_data_dict = {}
for attempts, value in seq_bin_data_list:
    if attempts not in seq_bin_data_dict:
        seq_bin_data_dict[attempts] = []
    seq_bin_data_dict[attempts].append(value)

# Extracting data
seq_bin_attempts_list = []
seq_bin_means = []
seq_bin_std_devs = []
for attempts, values in seq_bin_data_dict.items():
    seq_bin_attempts_list.append(attempts)
    seq_bin_means.append(np.mean(values))
    seq_bin_std_devs.append(np.std(values))

# Computing "normalized" data
seq_bin_norm_data_dict = {}
for attempts, value in seq_bin_norm_data_list:
    if attempts not in seq_bin_norm_data_dict:
        seq_bin_norm_data_dict[attempts] = []
    seq_bin_norm_data_dict[attempts].append(value)

seq_bin_norm_attempts_list = []
seq_bin_norm_means = []
seq_bin_norm_std_devs = []
for attempts, values in seq_bin_norm_data_dict.items():
    seq_bin_norm_attempts_list.append(attempts)
    seq_bin_norm_means.append(np.mean(values))
    seq_bin_norm_std_devs.append(np.std(values))

####################################################

# Processing sequential string data
seq_str_data_dict = {}
for attempts, value in seq_str_data_list:
    if attempts not in seq_str_data_dict:
        seq_str_data_dict[attempts] = []
    seq_str_data_dict[attempts].append(value)

# Extracting data
seq_str_attempts_list = []
seq_str_means = []
seq_str_std_devs = []
for attempts, values in seq_str_data_dict.items():
    seq_str_attempts_list.append(attempts)
    seq_str_means.append(np.mean(values))
    seq_str_std_devs.append(np.std(values))

# Computing "normalized" data
seq_str_norm_data_dict = {}
for attempts, value in seq_str_norm_data_list:
    if attempts not in seq_str_norm_data_dict:
        seq_str_norm_data_dict[attempts] = []
    seq_str_norm_data_dict[attempts].append(value)

seq_str_norm_attempts_list = []
seq_str_norm_means = []
seq_str_norm_std_devs = []
for attempts, values in seq_str_norm_data_dict.items():
    seq_str_norm_attempts_list.append(attempts)
    seq_str_norm_means.append(np.mean(values))
    seq_str_norm_std_devs.append(np.std(values))

####################################################

# Processing parallel binary data
par_str_data_dict = {}
for attempts, value in par_str_data_list:
    if attempts not in par_str_data_dict:
        par_str_data_dict[attempts] = []
    par_str_data_dict[attempts].append(value)

# Extracting data
par_str_attempts_list = []
par_str_means = []
par_str_std_devs = []
for attempts, values in par_str_data_dict.items():
    par_str_attempts_list.append(attempts)
    par_str_means.append(np.mean(values))
    par_str_std_devs.append(np.std(values))

# Computing "normalized" data
par_str_norm_data_dict = {}
for attempts, value in par_str_norm_data_list:
    if attempts not in par_str_norm_data_dict:
        par_str_norm_data_dict[attempts] = []
    par_str_norm_data_dict[attempts].append(value)

par_str_norm_attempts_list = []
par_str_norm_means = []
par_str_norm_std_devs = []
for attempts, values in par_str_norm_data_dict.items():
    par_str_norm_attempts_list.append(attempts)
    par_str_norm_means.append(np.mean(values))
    par_str_norm_std_devs.append(np.std(values))

# Plotting
fig, ax1 = plt.subplots(figsize=(7, 5))
ax1.errorbar(par_bin_attempts_list, par_bin_means, yerr=par_bin_std_devs, fmt='o-', label='Parallel bitwise', capsize=4, capthick=1)
ax1.errorbar(seq_bin_attempts_list, seq_bin_means, yerr=seq_bin_std_devs, fmt='o-', label='Sequential bitwise', capsize=4, capthick=1)
ax1.errorbar(par_str_attempts_list, par_str_means, yerr=par_str_std_devs, fmt='o-', label='Parallel string', capsize=4, capthick=1)
ax1.errorbar(seq_str_attempts_list, seq_str_means, yerr=seq_str_std_devs, fmt='o-', label='Sequential string', capsize=4, capthick=1)
ax1.set_xscale('log')
ax1.set_yscale('log')
ax1.set_xlabel('attempts')
ax1.set_ylabel('us')
ax1.set_title("Average us per attempts")
ax1.legend()
ax1.grid(True)
ax1.grid(which='minor', axis='y', linestyle=':', linewidth='0.3', color='gray')
plt.savefig('./output/attempts_us')

fig, ax2 = plt.subplots(figsize=(7, 5))
ax2.errorbar(par_bin_norm_attempts_list, par_bin_norm_means, yerr=par_bin_norm_std_devs, fmt='o-', label='Parallel bitwise', capsize=4, capthick=1)
ax2.errorbar(seq_bin_norm_attempts_list, seq_bin_norm_means, yerr=seq_bin_norm_std_devs, fmt='o-', label='Sequential bitwise', capsize=4, capthick=1)
ax2.errorbar(par_str_norm_attempts_list, par_str_norm_means, yerr=par_str_norm_std_devs, fmt='o-', label='Parallel string', capsize=4, capthick=1)
ax2.errorbar(seq_str_norm_attempts_list, seq_str_norm_means, yerr=seq_str_norm_std_devs, fmt='o-', label='Sequential string', capsize=4, capthick=1)
ax2.set_xscale('log')
ax2.set_xlabel('attempts')
ax2.set_ylabel('Normalized us')
ax2.set_title('"Normalized" us per attempts')
ax2.legend()
ax2.grid(True)
ax2.grid(which='minor', axis='y', linestyle=':', linewidth='0.3', color='gray')
ax2.yaxis.set_minor_locator(MultipleLocator(base=5))
plt.savefig('./output/normalized_attempts_us')

fig, ax3 = plt.subplots(figsize=(7, 5))
ax3.scatter([point[0] for point in par_bin_data_list], [point[1]/point[0] for point in par_bin_data_list], label="Parallel bitwise")
ax3.set_xscale('log')
ax3.set_xlabel('attempts')
ax3.set_ylabel('Normalized us')
ax3.set_title('"Normalized" us per attempts single points')
ax3.legend()
ax3.grid(True)
ax3.grid(which='minor', axis='y', linestyle=':', linewidth='0.3', color='gray')
ax3.yaxis.set_minor_locator(MultipleLocator(base=5))
plt.savefig('./output/normalized_attempts_us_single_points')

if TEST_MULTITHREAD_DONE:
    n_multithread = [4, 6, 8, 10, 12]

    multithread_results_binary = {}

    for test_n in n_multithread:
        test_file = f"./output/output_multithread_test_parallel_binary_nthreads_{test_n}.txt"
        with open(test_file, 'r') as file:
            file_data = file.read()
        pattern = re.compile(r'(\d+) ms')
        file_matches = pattern.findall(file_data)
        multithread_results_binary[test_n] = int(file_matches[0])
    
    multithread_results_string = {}
    for test_n in n_multithread:
        test_file = f"./output/output_multithread_test_parallel_string_nthreads_{test_n}.txt"
        with open(test_file, 'r') as file:
            file_data = file.read()
        pattern = re.compile(r'(\d+) ms')
        file_matches = pattern.findall(file_data)
        multithread_results_string[test_n] = int(file_matches[0])

    fig, axes = plt.subplots(ncols=1, nrows=2, figsize=(7, 10))
    axes[0].plot(multithread_results_binary.keys(), multithread_results_binary.values(), marker=".", markersize=12, color="blue", label="Parallel bitwise")
    axes[0].set_ylabel('ms')
    axes[0].set_title('Benchmark execution time')
    axes[0].legend()
    axes[0].grid(True)
    axes[0].grid(which='minor', axis='y', linestyle=':', linewidth='0.3', color='gray')
    axes[1].plot(multithread_results_string.keys(), multithread_results_string.values(), marker=".", markersize=12, color="green", label="Parallel string")
    axes[1].set_xlabel('# of threads')
    axes[1].set_ylabel('ms')
    axes[1].legend()
    axes[1].grid(True)
    axes[1].grid(which='minor', axis='y', linestyle=':', linewidth='0.3', color='gray')
    
    plt.tight_layout()
    plt.savefig('./output/multithread_test_ms')