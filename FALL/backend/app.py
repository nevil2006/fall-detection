print("🔥 FALL DETECTION BACKEND STARTED 🔥")

from flask import Flask, request, jsonify
import joblib
import numpy as np
from flask_cors import CORS
from datetime import datetime
import os

app = Flask(__name__)
CORS(app)

# ✅ Load model (make sure this file exists in backend folder)
MODEL_PATH = os.path.join(os.path.dirname(__file__), "fall_model.pkl")
model = joblib.load(MODEL_PATH)

# Store system status
system_status = {
    "last_prediction": 0,
    "last_updated": None
}

# ✅ Home route
@app.route("/", methods=["GET"])
def home():
    return "Fall Detection Backend Running Successfully!"

# ✅ Prediction route
@app.route("/predict", methods=["POST"])
def predict():
    try:
        data = request.json

        features = np.array([[
            data["acc_mean"],
            data["acc_max"],
            data["acc_std"],
            data["gyro_mean"],
            data["gyro_max"],
            data["gyro_std"]
        ]])

        prediction = int(model.predict(features)[0])

        system_status["last_prediction"] = prediction
        system_status["last_updated"] = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        return jsonify({
            "prediction": prediction
        })

    except Exception as e:
        return jsonify({"error": str(e)})

# ✅ Status route
@app.route("/status", methods=["GET"])
def status():
    return jsonify(system_status)

# ✅ Run server
if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000, debug=True)
