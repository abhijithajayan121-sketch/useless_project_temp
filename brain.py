import cv2
import serial
import serial.tools.list_ports
import time
import random
import math
import mediapipe as mp

# ==========================================
# 1. SERIAL PORT SETUP
# ==========================================
def find_arduino_port():
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        if "Arduino" in p.description or "CH340" in p.description or "FTDI" in p.description:
            return p.device
    return 'COM8'  # Default fallback COM port

SERIAL_PORT = find_arduino_port()
BAUD_RATE = 9600

try:
    arduino = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    time.sleep(2)
    print(f"Connected to Arduino on {SERIAL_PORT}")
except Exception as e:
    print(f"Serial Error: {e}")
    arduino = None

# ==========================================
# 2. MEDIAPIPE EYE TRACKING SETUP
# ==========================================
mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(
    max_num_faces=1,
    refine_landmarks=True,
    min_detection_confidence=0.5,
    min_tracking_confidence=0.5
)

cap = cv2.VideoCapture(0)

def is_eye_open(frame):
    """Calculates Eye Aspect Ratio (EAR) to detect open/closed eye state."""
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = face_mesh.process(rgb_frame)
    
    if not results.multi_face_landmarks:
        return False  # No face visible = treated as eyes closed

    landmarks = results.multi_face_landmarks[0].landmark
    h, w, _ = frame.shape

    p_top = (int(landmarks[385].x * w), int(landmarks[385].y * h))
    p_bot = (int(landmarks[380].x * w), int(landmarks[380].y * h))
    p_left = (int(landmarks[362].x * w), int(landmarks[263].y * h))
    p_right = (int(landmarks[263].x * w), int(landmarks[362].y * h))

    vertical_dist = math.dist(p_top, p_bot)
    horizontal_dist = math.dist(p_left, p_right)

    if horizontal_dist == 0:
        return False

    ear = vertical_dist / horizontal_dist
    return ear > 0.18

# ==========================================
# 3. SOLUTION GENERATORS
# ==========================================
def get_correct_answer(n1, op, n2):
    if op == '/' and n2 == 0:
        return "div0 error"
    if op == '+': return str(n1 + n2)
    if op == '-': return str(n1 - n2)
    if op == '*': return str(n1 * n2)
    if op == '/': return str(round(n1 / n2, 1))

def get_wrong_answer(n1, op, n2):
    if op == '/' and n2 == 0:
        return random.choice(["Ans: infinity", "Ans: 0", "Ans: 42"])
    
    correct = eval(f"{n1} {op} {n2}") if not (op == '/' and n2 == 0) else 0
    offset = random.choice([-10, -5, -1, 1, 3, 7, 12, 100])
    wrong_val = round(correct + offset, 1)
    
    insults = [
        f"Ans:{wrong_val} (easy)",
        f"It is {wrong_val}",
        f"Ans:{wrong_val}, idiot",
        f"Result: {wrong_val}"
    ]
    return random.choice(insults)

# ==========================================
# 4. MAIN LOOP WITH LIVE EYE SWAPPING
# ==========================================
current_equation = None
last_rendered_state = None

print("\n--- Arrogant Calculator Engine Active ---")
print("Eyes OPEN = Wrong Answer | Eyes CLOSED = Correct Answer")
print("Press 'q' in the camera window to quit.\n")

while True:
    ret, frame = cap.read()
    if not ret:
        break

    eyes_open = is_eye_open(frame)

    # 1. Read input request from Arduino
    if arduino and arduino.in_waiting > 0:
        raw_data = arduino.readline().decode('utf-8', errors='ignore').strip()
        parts = raw_data.split(',')
        if len(parts) == 3:
            try:
                n1 = int(parts[0])
                op = parts[1]
                n2 = int(parts[2])
                current_equation = (n1, op, n2)
                last_rendered_state = None  # Reset tracking state for fresh calculation
                print(f"\nNew Equation Received: {n1} {op} {n2}")
            except ValueError:
                pass

    # 2. Dynamic swapping logic
    if current_equation is not None:
        n1, op, n2 = current_equation
        
        # User has eyes OPEN -> Swap to WRONG answer
        if eyes_open and last_rendered_state != "WRONG":
            response_msg = get_wrong_answer(n1, op, n2)
            last_rendered_state = "WRONG"
            print(f"[EYES OPEN] Displaying WRONG answer: {response_msg}")
            if arduino:
                arduino.write((response_msg + "\n").encode('utf-8'))

        # User has eyes CLOSED -> Swap to CORRECT answer
        elif not eyes_open and last_rendered_state != "CORRECT":
            correct_val = get_correct_answer(n1, op, n2)
            response_msg = f"Ans: {correct_val}"
            last_rendered_state = "CORRECT"
            print(f"[EYES CLOSED] Displaying CORRECT answer: {response_msg}")
            if arduino:
                arduino.write((response_msg + "\n").encode('utf-8'))

    # Render video status overlay
    status_label = "EYES OPEN -> WRONG ANSWERS" if eyes_open else "EYES CLOSED -> CORRECT ANSWERS"
    color = (0, 0, 255) if eyes_open else (0, 255, 0)
    cv2.putText(frame, status_label, (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.6, color, 2)
    cv2.imshow("Arrogant Eye Monitor", frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
if arduino:
    arduino.close()