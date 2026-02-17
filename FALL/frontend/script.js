async function fetchStatus() {
    try {
        const response = await fetch("http://127.0.0.1:5000/status");
        const data = await response.json();

        const resultElement = document.getElementById("result");

        if (data.last_prediction === 1) {
            resultElement.innerText = "🚨 FALL DETECTED!";
            resultElement.style.color = "red";
        } else {
            resultElement.innerText = "✅ Normal";
            resultElement.style.color = "green";
        }

    } catch (error) {
        console.error("Backend connection error:", error);
        document.getElementById("result").innerText = "⚠ Backend Offline";
    }
}

// refresh every 2 seconds
setInterval(fetchStatus, 2000);

// run immediately
fetchStatus();
