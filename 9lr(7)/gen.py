
import os, sys
import random
import string
import subprocess
import time

num_max = 50
nums = []
times = []

exec_path  = "solution/solution"
pic_fold = ""

mean_cnt = 1000
auto_test = True
build_benchmark = True

test = open("test.txt", "w")

def gen_testes(a):
    n = a
    m = 50
    out = ""
    out += str(m) + ' ' + str(n) + '\n'
    for _i in range(m):
        for _j in range(n):
            out += str(random.randint(0, 50)) + ' '
        out += str(random.randint(1, 50)) + '\n'
    return out

#test.write(gen_testes(5))
if auto_test:
    for i in range(20):
        num = int(num_max / (1.1 ** i))
        print("running test for", num)
        time_sum = 0
        for _j in range(mean_cnt):
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
            time_sum += time_taken
            process.stdin.close()
            #print("time taken for {} numbers: \t{}".format(num, time_taken))
        print("avarege time taken for {} numbers: \t{}".format(num, time_taken))
        nums.append(num)
        times.append(time_sum / mean_cnt)

if build_benchmark:
    import matplotlib.pyplot as plt
    plt.suptitle('Benchmark')
    plt.plot(nums, times)
    #plt.gca().invert_yaxis()
    
    plt.xlabel('n quantity')
    plt.ylabel('time taken (sec)')

    print("saving plt")
    plt.savefig(os.path.join(pic_fold, "benchmark.png"), bbox_inches='tight')
    # plt.savefig("test.png",bbox_inches='tight')
    print("saved")
    plt.show()

test.close()
    