# -*- coding: utf-8 -*-
"""
Created on Thu Dec 12 10:50:02 2024

@author: Shane
"""

import numpy as np
import matplotlib.pyplot as plot

def softmax(nums):
    return np.exp(nums - np.max(nums))/sum(np.exp(nums - np.max(nums)))

def gradient_descent_U(V, P):
    grad = np.add(-1 * np.array(V),P * np.array(V))
    return grad

def gradient_descent_V(U,P,context):
    result = np.array(U[context]) * -1
    for j in range(len(vocab)):
        result += (P[j] * np.array(U[j]))
    return result


window_size = 2
embedding_dimension = 128
epoch = 100
alpha = 0.005
file = "training.txt"

sentences = []
vocab = []
total_words = 0


with open(file, encoding='latin-1') as f:
    for line in f:
        sentences.append(line.rstrip('\n').lower().split())
for sentence in sentences:
    for word in sentence:
        total_words += 1
        if word not in vocab:
            vocab.append(word.lower())
        
U = np.random.rand(len(vocab),embedding_dimension)
V = np.random.rand(len(vocab),embedding_dimension)


x = list(range(1,epoch+1))
J = []
J_avg = []

for e in range(0,epoch):
    U_grad = np.zeros((len(vocab),embedding_dimension))
    V_grad = np.zeros((len(vocab),embedding_dimension))
   
    num_context = 0
    
    for sentence in sentences:
        for center in sentence:
            context_words = []
            vc = []
            P = []
            
            vc = V[vocab.index(center)]
            P = np.dot(U,vc)
            P = softmax(P)
            vc = vc[None, ...]
            P = P[...,None]
            L = 0
            
            temp_J = 1
            
            for i in range (sentence.index(center) - window_size, sentence.index(center) + window_size + 1):
                if (not i < 0) and (not i > len(sentence)-1) and (not i == sentence.index(center)):
                    context_words.append(sentence[i])
                    U_grad[vocab.index(sentence[i]),None] += gradient_descent_U(vc, P[vocab.index(sentence[i])])
                    V_grad[vocab.index(center),None] += gradient_descent_V(U, P,vocab.index(sentence[i]))
                    temp_J += np.log(P[i])
                    num_context += 1
                    
    temp_J =-1 * temp_J
    J.append(temp_J[0])
    J_avg.append(temp_J[0]/num_context)
    U = np.array(U) - alpha * np.array(U_grad)
    V = np.array(V) - alpha * np.array(V_grad)
    print("Progress: " + str(e+1) + "/" + str(epoch))
final_matrix = U + V    
fig, ax = plot.subplots()
ax.plot(x,J)
ax.set_xlabel("epoch")
ax.set_ylabel("Averaged error")
plot.show
    