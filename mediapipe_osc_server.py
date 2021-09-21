import cv2
import mediapipe as mp

from pythonosc.udp_client import SimpleUDPClient

import time


def calculate_fps():
	new_time = time.time()
	fps = 1/(new_time - calculate_fps.prev_time)
	calculate_fps.prev_time = new_time
	return fps
calculate_fps.prev_time = 0.0


mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_holistic = mp.solutions.holistic

osc_client = SimpleUDPClient("127.0.0.1", 8000)  # Create client

cap = cv2.VideoCapture(0)
with mp_holistic.Holistic(min_detection_confidence=0.5, 
                          min_tracking_confidence=0.5,
						  model_complexity=1) as holistic:
  while cap.isOpened():
    success, image = cap.read()
    if not success:
      print("Ignoring empty camera frame.")
      # If loading a video, use 'break' instead of 'continue'.
      continue

    # Flip the image horizontally for a later selfie-view display
    image = cv2.flip(image, 1)
    # Convert the BGR image to RGB.
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    # To improve performance, optionally mark the image as not writeable to pass by reference.
    image.flags.writeable = False
    results = holistic.process(image)
	
    # Draw landmark annotation on the image.
    image.flags.writeable = True
    image = cv2.cvtColor(image, cv2.COLOR_RGB2BGR)
    mp_drawing.draw_landmarks(
        image,
        results.pose_landmarks,
        mp_holistic.POSE_CONNECTIONS,
        landmark_drawing_spec=mp_drawing_styles.get_default_pose_landmarks_style())
    mp_drawing.draw_landmarks(
        image,
        results.face_landmarks,
        mp_holistic.FACEMESH_CONTOURS,
        landmark_drawing_spec=None,
        connection_drawing_spec=mp_drawing_styles.get_default_face_mesh_contours_style())
    mp_drawing.draw_landmarks(
        image,
        results.face_landmarks,
        mp_holistic.FACEMESH_TESSELATION,
        landmark_drawing_spec=None,
        connection_drawing_spec=mp_drawing_styles.get_default_face_mesh_tesselation_style())
    mp_drawing.draw_landmarks(
        image,
        results.left_hand_landmarks,
        mp_holistic.HAND_CONNECTIONS,
        mp_drawing_styles.get_default_hand_landmarks_style(),
        mp_drawing_styles.get_default_hand_connections_style())
    mp_drawing.draw_landmarks(
        image,
        results.right_hand_landmarks,
        mp_holistic.HAND_CONNECTIONS,
        mp_drawing_styles.get_default_hand_landmarks_style(),
        mp_drawing_styles.get_default_hand_connections_style())
    
    # Send the landmarks through OSC
    if results.pose_landmarks is None:
        osc_client.send_message("/mediapipe_osc_server/pose/tracking", False)
    else:
        osc_client.send_message("/mediapipe_osc_server/pose/tracking", True)
        for idx, landmark in enumerate(results.pose_landmarks.landmark):
            osc_client.send_message("/mediapipe_osc_server/pose/" + str(idx), [landmark.x, landmark.y, landmark.z])
            osc_client.send_message("/mediapipe_osc_server/pose/" + str(idx) + "/visibility", landmark.visibility)
    
    if results.face_landmarks is None:
        osc_client.send_message("/mediapipe_osc_server/face/tracking", False)
    else:
        osc_client.send_message("/mediapipe_osc_server/face/tracking", True)
        for idx, landmark in enumerate(results.face_landmarks.landmark):
            osc_client.send_message("/mediapipe_osc_server/face/" + str(idx), [landmark.x, landmark.y, landmark.z])
            osc_client.send_message("/mediapipe_osc_server/face/" + str(idx) + "/visibility", landmark.visibility)
    
    if results.left_hand_landmarks is None:
        osc_client.send_message("/mediapipe_osc_server/hands/left/tracking", False)
    else:
        osc_client.send_message("/mediapipe_osc_server/hands/left/tracking", True)
        for idx, landmark in enumerate(results.left_hand_landmarks.landmark):
            osc_client.send_message("/mediapipe_osc_server/hands/left/" + str(idx), [landmark.x, landmark.y, landmark.z])
            osc_client.send_message("/mediapipe_osc_server/hands/left/" + str(idx) + "/visibility", landmark.visibility)
    
    if results.right_hand_landmarks is None:
        osc_client.send_message("/mediapipe_osc_server/hands/right/tracking", False)
    else:
        osc_client.send_message("/mediapipe_osc_server/hands/right/tracking", True)
        for idx, landmark in enumerate(results.right_hand_landmarks.landmark):
            osc_client.send_message("/mediapipe_osc_server/hands/right/" + str(idx), [landmark.x, landmark.y, landmark.z])
            osc_client.send_message("/mediapipe_osc_server/hands/right/" + str(idx) + "/visibility", landmark.visibility)
    
    # Calculate and draw fps
    cv2.putText(image, "fps: {:.2f}".format(calculate_fps()), (10,20), cv2.FONT_HERSHEY_PLAIN, 1, (255, 255, 255))
    
    cv2.imshow('MediaPipe Holistic', image)
    if cv2.waitKey(5) & 0xFF == 27:
      break
cap.release()