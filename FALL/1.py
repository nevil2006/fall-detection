import joblib
import numpy as np

model = joblib.load(r"C:\Users\ADMIN\OneDrive\Desktop\FALL\backend\fall_model.pkl")

sample = np.array([[12, 30, 5, 1, 4, 0.8]])

prediction = model.predict(sample)

print("Prediction:", prediction[0])
