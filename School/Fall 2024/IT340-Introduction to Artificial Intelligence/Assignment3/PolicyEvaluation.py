# -*- coding: utf-8 -*-
"""
Created on Wed Oct  9 17:47:19 2024

@author: Shane Stevens
"""

def evaluation(policy,reward):
    gamma = 0.8

    v_pi = {"a":0, "b":0, "c":0,"d":100}
    v_pi_sum = {"a":0, "b":0, "c":0,"d":100}
    
    # I know this is a lot of loops, but its the only way I can get close to the expected values
    # If I only do 100 loops, my numbers are significantly off
    for i in range(250000):
        for state in policy:
            action_1_p1 = .9 * (reward + gamma * (v_pi[policy[state][1][1]]))
            action_1_p2 = .1 * (reward + gamma * (v_pi[policy[state][2][1]]))
            action_2_p1 = .9 * (reward + gamma * (v_pi[policy[state][2][1]]))
            action_2_p2 = .1 * (reward + gamma * (v_pi[policy[state][1][1]]))
            action = policy[state][1][0] * (action_1_p1 + action_1_p2) + policy[state][2][0] * (action_2_p1 + action_2_p2)
            
            v_pi_sum[state] += action
            
            
        for state in policy:
            v_pi[state] = v_pi_sum[state]/(i+1)   


    return v_pi

reward = -10

policy_1 = {"a":{1:(1 ,"b"), 2:(0,"c")}, 
          "b":{1:(1 ,"d"), 2:(0,"a")},
          "c":{1:(1 ,"a"), 2:(0,"d")}}

policy_2 = {"a":{1:(0 ,"b"), 2:(1,"c")}, 
          "b":{1:(0 ,"d"), 2:(1,"a")},
          "c":{1:(0 ,"a"), 2:(1,"d")}}

policy_3 = {"a":{1:(0.4 ,"b"), 2:(0.6,"c")}, 
          "b":{1:(1 ,"d"), 2:(0,"a")},
          "c":{1:(0 ,"a"), 2:(1,"d")}}

eval_1 = evaluation(policy_1,reward)
eval_2 = evaluation(policy_2,reward)
eval_3 = evaluation(policy_3,reward)

print("Policy 1:")
for val in eval_1:
    print("vpi(" + val + ") = " + str(round(eval_1[val],2))) 
print("")

print("Policy 2:")
for val in eval_2:
    print("vpi(" + val + ") = " + str(round(eval_2[val],2)))
print("")

print("Policy 3:")
for val in eval_3:
    print("vpi(" + val + ") = " + str(round(eval_3[val],2)))

