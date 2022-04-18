import cv2

cap = cv2.VideoCapture(0) # default camera

while cap.isOpened():
    # 카메라 프레임 읽기
    success, frame = cap.read()
    if success:
        cv2.imshow('Camera Window',frame)

        key = cv2.waitKey(1) & 0xFF
        if key == 27:
            break

cap.release()
