#!/usr/bin/env python
# coding: utf-8

# # Project 1

# In[1]:


# Python ≥3.5 is required
import sys
assert sys.version_info >= (3, 5)

# Scikit-Learn ≥0.20 is required
import sklearn
assert sklearn.__version__ >= "0.20"
print(sklearn.__version__)

# Common imports
import numpy as np
import os

# to make this notebook's output stable across runs
np.random.seed(42)

# To plot pretty figures
get_ipython().run_line_magic('matplotlib', 'inline')
import matplotlib as mpl
import matplotlib.pyplot as plt
mpl.rc('axes', labelsize=14)
mpl.rc('xtick', labelsize=12)
mpl.rc('ytick', labelsize=12)

# Where to save the figures
PROJECT_ROOT_DIR = "."
CHAPTER_ID = "decision_trees"
IMAGES_PATH = os.path.join(PROJECT_ROOT_DIR, "images", CHAPTER_ID)
os.makedirs(IMAGES_PATH, exist_ok=True)


# # Training and Visualizing a Decision Tree

# In[2]:


from sklearn.datasets import load_iris
from sklearn.tree import DecisionTreeClassifier

iris = load_iris()
X = iris.data[:, 2:] 
print(type(iris.data))
print(iris.data.shape)
print(iris.data.ndim)
print(iris.data.size)
y = iris.target
print("----- X ---")
print(X.size)
print(X.shape)
tree_clf = DecisionTreeClassifier(max_depth=2, random_state=42)   
tree_clf.fit(X, y)


# In[3]:


from graphviz import Source
from sklearn.tree import export_graphviz

export_graphviz(
        tree_clf,
        out_file=os.path.join(IMAGES_PATH, "iris_tree.dot"),
        feature_names=iris.feature_names[2:], 
        class_names=iris.target_names,
        rounded=True,
        filled=True
    )

Source.from_file(os.path.join(IMAGES_PATH, "iris_tree.dot"))


# In[4]:


from sklearn.model_selection import cross_val_score

cross_val_score(tree_clf, iris.data, iris.target).mean()


# In[5]:


from sklearn.model_selection import cross_val_score

cross_val_score(tree_clf, iris.data, iris.target, cv=10).mean()


# # --------- Project 1 starts here ------------

# In[6]:


# https://scikit-learn.org/stable/modules/generated/sklearn.model_selection.train_test_split.html
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier

X_train, X_test, y_train, y_test = train_test_split(iris.data, iris.target, 
                                                    test_size = 0.3, random_state=42)
tree_clf = DecisionTreeClassifier(max_depth=2, random_state=42)
tree_clf.fit(X_train, y_train)

export_graphviz(
        tree_clf,
        out_file=os.path.join(IMAGES_PATH, "iris_tree.dot2"),
        feature_names=iris.feature_names[:],  
        class_names=iris.target_names,
        rounded=True,
        filled=True
    )

Source.from_file(os.path.join(IMAGES_PATH, "iris_tree.dot2"))


# In[7]:


rnd_clf = RandomForestClassifier(n_estimators=500, random_state=42)
rnd_clf.fit(X_train, y_train)

# ----- add here the naive bayes classification method. -----


# ----- update the following lines to include the instances of 
# ----- naive bayes classfication method
models = [("DT", tree_clf), ("RF", rnd_clf)]
unsorted_scores = [(name, cross_val_score(model, X_train, y_train, cv=10).mean()) 
                   for name, model in models]
scores = sorted(unsorted_scores, key=lambda x: x[1])
print(scores)  


# In[8]:


from sklearn.metrics import classification_report, accuracy_score

# msnually select the best classfication method and compare the individual accuracy
y_pred = rnd_clf.predict(X_test)
print(accuracy_score(y_test, y_pred))

y_pred = tree_clf.predict(X_test)
print(accuracy_score(y_test, y_pred))

# ---- Write the process for automatically identifying 
# the best classification method using cross-validation
#



# ---- predict the target class of each testing example


# In[9]:


from sklearn.metrics import confusion_matrix
from sklearn.metrics import ConfusionMatrixDisplay

cm = confusion_matrix(y_test, y_pred)
cm_display = ConfusionMatrixDisplay(cm, display_labels=iris.target_names).plot()


# In[10]:


print(classification_report(y_test, y_pred, target_names=iris.target_names))


# In[ ]:





# In[ ]:





# In[ ]:




