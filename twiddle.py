import os


def start_simulator():
    os.system("twiddle\start_pid_simulator.exe")

count = 0
def run(p):
    global count
    count += 1
    return 1-0.05*count

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
