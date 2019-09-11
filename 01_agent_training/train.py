#%%
import numpy as np
from dataset import read_dataset
from sklearn.linear_model import LinearRegression
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.multioutput import MultiOutputRegressor
from sklearn.svm import SVR, LinearSVR

#%%
DIMS = 4
X, y = read_dataset(DIMS)
print(X.shape, y.shape)

X = X / DIMS
y = (y * 2) - 1

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.20, random_state=42)

#%%
def train_and_score(model):
    print("Fitting {}".format(model))
    model.fit(X_train, y_train)
    print("Score: {}".format(model.score(X_test, y_test)))
    return model

rfr = train_and_score(RandomForestRegressor(n_estimators=20, max_depth=12, random_state=42))
lr = train_and_score(LinearRegression())

m_svr = train_and_score(MultiOutputRegressor(LinearSVR()))
m_lr = train_and_score(MultiOutputRegressor(LinearRegression()))