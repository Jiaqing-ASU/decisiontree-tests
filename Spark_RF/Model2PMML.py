from sklearn.ensemble import RandomForestClassifier
import pandas
import pickle
import joblib
import time
from sklearn2pmml import sklearn2pmml
from pypmml import Model
from six import StringIO
import pydotplus
import sklearn_pandas
from sklearn2pmml.pipeline import PMMLPipeline
from sklearn.tree import export_graphviz
from IPython.display import Image
import graphviz
import os

filename = 'rf-10-8-6.pkl'
model = joblib.load(filename)
pipeline_model = PMMLPipeline([('rf-higgs', model)])
sklearn2pmml(pipeline_model, "rf-10-8-6.pmml")

X_data = pandas.read_csv("HIGGS.csv",usecols=[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28])
X_test = X_data[0:5]

pmml_model = Model.load("rf-10-8-6.pmml")
print(pmml_model.predict(X_test))