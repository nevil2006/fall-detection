import os
from twilio.rest import Client

# Load credentials from environment variables
TWILIO_ACCOUNT_SID = os.getenv("TWILIO_ACCOUNT_SID")
TWILIO_AUTH_TOKEN = os.getenv("TWILIO_AUTH_TOKEN")
TWILIO_PHONE_NUMBER = os.getenv("TWILIO_PHONE_NUMBER")
ALERT_PHONE_NUMBER = os.getenv("ALERT_PHONE_NUMBER")

# Safety check
if not all([TWILIO_ACCOUNT_SID, TWILIO_AUTH_TOKEN, TWILIO_PHONE_NUMBER, ALERT_PHONE_NUMBER]):
    raise ValueError("❌ Twilio environment variables are not set properly")

# Create Twilio client
client = Client(TWILIO_ACCOUNT_SID, TWILIO_AUTH_TOKEN)

def send_fall_alert():
    """
    Sends SMS and makes a call when a fall is detected
    """

    # Send SMS
    sms = client.messages.create(
        body="🚨 FALL DETECTED! Please check immediately!",
        from_=TWILIO_PHONE_NUMBER,
        to=ALERT_PHONE_NUMBER
    )
    print("✅ SMS sent:", sms.sid)

    # Make Call
    call = client.calls.create(
        twiml="""
        <Response>
            <Say voice="alice">
                Alert. Fall detected. Please check immediately.
            </Say>
        </Response>
        """,
        from_=TWILIO_PHONE_NUMBER,
        to=ALERT_PHONE_NUMBER
    )
    print("📞 Call initiated:", call.sid)


# Run directly (for testing)
if __name__ == "__main__":
    send_fall_alert()
