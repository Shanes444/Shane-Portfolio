# -*- coding: utf-8 -*-
"""
Created on Fri Mar 10 11:06:46 2017

@author: xfang13
Shane Stevens
"""
from os import walk
import numpy as np

#seed = 12345
seed = np.random.randint(100000)

number_of_training_emails = 500

ham_dir = 'Ham'
All_Ham = []
for (dirpath, dirnames, filenames) in walk(ham_dir):
    if filenames != []:
        for ham in filenames:
            with open(dirpath+'\\'+ham) as f:
                #read the file as a big string
                All_Ham.append(f.read())
                
spam_dir = 'Spam'
All_Spam = []
for (dirpath, dirnames, filenames) in walk(spam_dir):
    if filenames != []:
        for spam in filenames:
            with open(dirpath+'\\'+spam,encoding='latin-1') as f:
                #read the file as a big string
                All_Spam.append(f.read())           
                

randomState = np.random.RandomState(seed)
randomState.shuffle(All_Ham)
randomState.shuffle(All_Spam)

training_data = All_Ham[:number_of_training_emails] + All_Spam[:number_of_training_emails]
testing_data = All_Ham[number_of_training_emails:] + All_Spam[number_of_training_emails:] 

#important: use .split() to separate the words 

#create dictionary containing counts of all words
word_dict = {}

for email in training_data:
    for word in email.split():
        if word not in word_dict:
            word_dict[word] = {0: 0, 1: 0}
        if training_data.index(email) < number_of_training_emails:
            word_dict[word][0] += 1
        else:
            word_dict[word][1] += 1
            
p_spam = number_of_training_emails/(number_of_training_emails*2)
p_not_spam = 1 - p_spam

is_spam = []
predicted_spam = []

for email in testing_data:
    email_ham_probability = p_not_spam
    email_spam_probability = p_spam
    for word in email.split():
        if word in word_dict.keys():
            word_prob_ham = (word_dict[word][0] + 1)/(number_of_training_emails + len(word_dict))
            word_prob_spam = (word_dict[word][1] + 1)/(number_of_training_emails + len(word_dict))
        else:
           word_prob_ham = 1/(number_of_training_emails+len(word_dict))
           word_prob_spam = 1/(number_of_training_emails+len(word_dict)) 
        
        email_ham_probability = email_ham_probability * word_prob_ham
        email_spam_probability = email_spam_probability * word_prob_spam
        
    #print(str(email_ham_probability) + " : " + str(email_spam_probability))
    if email_ham_probability <= email_spam_probability:
        predicted_spam.append(1)
    else:
        predicted_spam.append(0)


    if testing_data.index(email) < len(testing_data)/2:
        is_spam.append(0)
    else:
        is_spam.append(1)

true_spam = 0;
false_spam = 0;
true_ham = 0;
false_ham = 0;

for index in range(len(predicted_spam)):
    if is_spam[index] == 0 and predicted_spam[index] == 0:
        true_ham += 1
    elif is_spam[index] == 0 and predicted_spam[index] == 1:
        false_spam += 1
    elif is_spam[index] == 1 and predicted_spam[index] == 1:
        true_spam += 1
    else:
        false_ham += 1
        
print("true ham: " + str(true_ham))
print("false ham: " + str(false_ham))
print("true spam: " + str(true_spam))
print("false spam: " + str(false_spam) + "\n")  

#calculate accuracy, precision, recall, and F1
accuracy = (true_ham + true_spam)/(true_ham + false_ham + true_spam + false_spam)
precision = true_spam/(true_spam + false_spam)
recall = true_spam/(true_spam + false_ham)
F1 = (2 * precision * recall)/(precision + recall)

print("accuracy:" + str(accuracy))
print("precision: " + str(precision))
print("recall: " + str(recall))
print("F1 score: " + str(F1))

#print(predicted_spam)
#print(is_spam)
        
        