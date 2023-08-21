# Import Libraries
import cv2
import numpy as np
import time
import socket

# Serial Communication with Arduino
# host = '192.168.87.24'
# port = 1234
# client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# client_socket.connect((host, port))

# HSV Color (Orange and Green)

# Orange
lower_orange = np.array([10, 130, 170])
upper_orange = np.array([28, 210, 255])
# Green
# lower_green = np.array([30, 40, 66])
# upper_green = np.array([70, 255, 255])
lower_green1 = np.array([35, 50, 50])  # Adjust the lower threshold for the first shade
upper_green1 = np.array([70, 255, 255])  # Adjust the upper threshold for the first shade

lower_green2 = np.array([70, 50, 50])  # Adjust the lower threshold for the second shade
upper_green2 = np.array([90, 255, 255])  # Adjust the upper threshold for the second shade
# Timestamp Array
timestamps = []

# Initialize the webcam and time
cap = cv2.VideoCapture(0)
start_time = time.time()

# ESP32-Cam URL
#URL = 'http://192.168.87.24'
cv2.namedWindow("live transmission", cv2.WINDOW_AUTOSIZE)
#AWB = True
#cap = cv2.VideoCapture(URL+':81/stream')
# input_path = 'b.mp4'  # Replace with the actual input video file path
# cap = cv2.VideoCapture(input_path)
# start_time = time.time()
width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
# Initialize object counts and statuses
orange_object_count = 0
orange_object_status = []
green_object_count = 0
green_object_status = []

# Number of frames an object should be absent before incrementing the count
absent_frames_threshold = 120
frames_since_last_detection_orange = 0
frames_since_last_detection_green = 0

# Loop
while True:
    # Read the frame from the webcam
    #cap = cv2.VideoCapture(URL+'cam-lo.jpg')
    ret, frame = cap.read()
    #img_resp=urllib.request.urlopen(URL+'cam-hi.jpg')
    #imgnp=np.array(bytearray(img_resp.read()),dtype=np.uint8)
    #frame=cv2.imdecode(imgnp,-1)

    if not ret:
        break

    # Convert the frame to HSV color space
    
    hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

    # Create a mask for orange and green objects
    orange_mask = cv2.inRange(hsv_frame, lower_orange, upper_orange)
    mask1 = cv2.inRange(hsv_frame, lower_green1, upper_green1)

    # Create the second mask based on the second green color thresholds
    mask2 = cv2.inRange(hsv_frame, lower_green2, upper_green2)

    # Combine the masks using bitwise OR operation
    green_mask = cv2.bitwise_or(mask1, mask2)
    #green_mask = cv2.inRange(hsv_frame, lower_green, upper_green)

    # Find contours of orange and green objects
    orange_contours, _ = cv2.findContours(orange_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    green_contours, _ = cv2.findContours(green_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # Update object statuses for current frame
    current_orange_status = [False] * len(orange_object_status)
    current_green_status = [False] * len(green_object_status)

    # Look for orange object (straw)
    for i, contour in enumerate(orange_contours):
        # Calculate area of each orange contour
        area = cv2.contourArea(contour)

        # Get bounding rectangle of contour
        x, y, w, h = cv2.boundingRect(contour)

        # Check if bounding rectangle is entirely within frame
        if x > 0 and y > 0 and x + w < frame.shape[1] and y + h < frame.shape[0]:
            # If the area is above a certain threshold, consider it a orange object
            if area > 15000000:
                # Check if object was previously on screen
                if i < len(orange_object_status) and orange_object_status[i]:
                    current_orange_status[i] = True
                # Otherwise, count as new
                else:
                    current_orange_status.append(True)

                # Draw a bounding box around orange object
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 165, 255), 2)
        else:
            current_orange_status.append(False)

    # Look for green objects
    for i, contour in enumerate(green_contours):
        # Calculate area of each green contour
        area = cv2.contourArea(contour)

        # Get bounding rectangle of contour
        x, y, w, h = cv2.boundingRect(contour)

        # Check if bounding rectangle is entirely within frame
        if x > 0 and y > 0 and x + w < frame.shape[1] and y + h < frame.shape[0]:
            # If area is above a certain threshold, consider it a green object
            if area > 100000:
                # Check if object was previously on screen
                if i < len(green_object_status) and green_object_status[i]:
                        current_green_status[i] = True
                # Otherwise, count as new object
                else:
                    current_green_status.append(True)
                    
                # Draw bounding box around green object
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        else:
            current_green_status.append(False)           

    # Update object status and counts
    orange_object_status = current_orange_status
    green_object_status = current_green_status

    # Check if any object has been absent for a certain number of frames
    if any(orange_object_status) and frames_since_last_detection_orange >= absent_frames_threshold:
            orange_object_count += 1
            frames_since_last_detection_orange = 0

    # If no object is present, increment the frame counter
    if not any(orange_object_status):
            frames_since_last_detection_orange += 1

    # Check if any object has been absent for a certain number of frames
    if any(green_object_status) and frames_since_last_detection_green >= absent_frames_threshold:
            green_object_count += 1
            timestamp = time.time() - start_time
            timestamps.append(timestamp)
            frames_since_last_detection_green = 0

    # If no object is present, increment the frame counter
    if not any(green_object_status):
            frames_since_last_detection_green += 1

    #rotated_frame = cv2.rotate(frame, cv2.ROTATE_90_COUNTERCLOCKWISE)
    
    # Display the count of objects
    cv2.putText(frame, f'Orange Objects: {orange_object_count}', (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 165, 255), 2)
    cv2.putText(frame, f'Green Objects: {green_object_count}', (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)

    cv2.imshow("live transmission", frame)

    # Display the frame
    #cv2.imshow('Frame', frame)


    # Exit the loop if 'q' is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the webcam and close the window
cap.release()
cv2.destroyAllWindows()

# Print out the array of timestamps
print("Timestamps for Green:")
for timestamp in timestamps:
    print(timestamp)

# Convert the array of integers to a string with comma delimiter
data_string = ','.join(map(str, timestamps))

# Send the data string to the ESP32-CAM
# Q

