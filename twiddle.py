import os
import os.path
import subprocess


def start_simulator():
    os.system("/mnt/c/Users/Ralf/git/CarND-PID-Control-Project/twiddle/start_pid_simulator.exe")

def run(p):
    proc = subprocess.Popen([os.path.join("build","pid"),
                             "-p", str(p[0]),
                             "-i", str(p[1]),
                             "-d", str(p[2]),
                             "-t", "120"], stdout=subprocess.PIPE, shell=False)
    (out, err) = proc.communicate()
    err = 0
    for i in out.splitlines():
        if b"Total Error:" in i:
            err = float(i[12:])
    return err

def twiddle(tol=0.2):
    p = [0, 0, 0]
    dp = [1, 1, 1]
    start_simulator()
    best_err = run(p)

    it = 0
    while sum(dp) > tol:
        print("Iteration {}, best error = {}, p = {}".format(it, best_err, p))
        for i in range(len(p)):
            p[i] += dp[i]
            start_simulator()
            err = run(p)

            if err < best_err:
                best_err = err
                dp[i] *= 1.1
            else:
                p[i] -= 2 * dp[i]
                start_simulator()
                err = run(p)

                if err < best_err:
                    best_err = err
                    dp[i] *= 1.1
                else:
                    p[i] += dp[i]
                    dp[i] *= 0.9
            print("   dp = {}, p = {}".format(dp,p))
        it += 1
    return p


params, err = twiddle()
print("Final twiddle error = {}".format(err))
print(params)
