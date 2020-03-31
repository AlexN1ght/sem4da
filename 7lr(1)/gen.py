
import os, sys
import random
import string

import subprocess

import time

num_max = 5000
nums = []
times = []

exec_path  = "solution/solution"
pic_fold = ""

build_benchmark = True

test = open("test.txt", "w")
def gen_testes(a):
    n = 50
    m = a
    out = ""
    out += str(n) + ' ' + str(m) + '\n'
    for i in range(n):
        a = random.randint(0, 100)
        b = random.randint(0, 100)
        out += str(a) + ' ' + str(b) + '\n'
    return out

for i in range(20):
        num = int(num_max / (1.3 ** i))
        print("\n\nrunning test for", num)

        process = subprocess.Popen(
                exec_path, stdin=subprocess.PIPE,
                # stderr=sys.stdout, bufsize=16384,
                stderr=sys.stdout, bufsize=8192,
                stdout=subprocess.PIPE)
        start_time = time.time() # start recording time
        # sub_output = ""
        # for i, line in enumerate(sub_input):
        #     print("entering {} entry {}".format(i, str(line)))
            # process.stdin.write((str(line)+"\n").encode('utf-8'))   # write to out prog
        process.communicate(gen_testes(num).encode('utf-8'))
        #time_taken = str((time.time() - start_time) / 60)  # capture the time
        time_taken = time.time() - start_time  # capture the time
        process.stdin.close()
        print("time taken {} for numbers: \t{}".format(num, time_taken))
        nums.append(num)
        times.append(time_taken)

if build_benchmark:
    import matplotlib.pyplot as plt
    plt.suptitle('Benchmark')
    # plt.plot(nums, times)
    plt.plot(nums, times)
    #plt.gca().invert_yaxis()
    
    plt.xlabel('m quantity')
    plt.ylabel('time taken (sec)')

    print("saving plt")
    plt.savefig(os.path.join(pic_fold, "benchmark.png"), bbox_inches='tight')
    # plt.savefig("test.png",bbox_inches='tight')
    print("saved")
    plt.show()
    