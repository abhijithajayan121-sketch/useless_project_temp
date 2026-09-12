from flask import Flask, jsonify
import cv2
import mediapipe as mp
import math
import threading

app = Flask(__name__)

# ==========================================
# MEDIAPIPE EYE TRACKING SETUP
# ==========================================
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(
    max_num_faces=1,
    refine_landmarks=True,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

cap = cv2.VideoCapture(0)
current_eye_state = False  # False = Closed/No Face, True = Open

def track_eyes():
    global current_eye_state
    while True:
        ret, frame = cap.read()
        if not ret:
            continue
        
        # Mirror the webcam feed horizontally
        frame = cv2.flip(frame, 1)
        
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = face_mesh.process(rgb_frame)
        
        if not results.multi_face_landmarks:
            current_eye_state = False
        else:
            landmarks = results.multi_face_landmarks[0].landmark
            h, w, _ = frame.shape

            p_top = (int(landmarks[385].x * w), int(landmarks[385].y * h))
            p_bot = (int(landmarks[380].x * w), int(landmarks[380].y * h))
            p_left = (int(landmarks[362].x * w), int(landmarks[263].y * h))
            p_right = (int(landmarks[263].x * w), int(landmarks[362].y * h))

            vertical_dist = math.dist(p_top, p_bot)
            horizontal_dist = math.dist(p_left, p_right)

            ear = vertical_dist / horizontal_dist if horizontal_dist != 0 else 0
            # Eye Aspect Ratio threshold (0.15 sensitive check)
            current_eye_state = ear > 0.15

        status_label = "EYES OPEN -> WRONG" if current_eye_state else "EYES CLOSED -> CORRECT"
        color = (0, 0, 255) if current_eye_state else (0, 255, 0)
        cv2.putText(frame, status_label, (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
        cv2.imshow("Eye Tracking Server", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

threading.Thread(target=track_eyes, daemon=True).start()

# ==========================================
# HTTP ENDPOINT (EYE STATUS ONLY)
# ==========================================
@app.route('/eye-status', methods=['GET'])
def get_eye_status():
    return jsonify({"eyes_open": current_eye_state})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)