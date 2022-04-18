import cv2

cap = cv2.VideoCapture(0) # default camera

# height, width setting
width = cap.get(cv2.CAP_PROP_FRAME_WIDTH)
height = cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
print("size: {0} x {1}".format(width,height))

# 영상 저장을 위한 VideoWriter
fourcc = cv2.VideoWriter_fourcc(*'XVID')
writer = cv2.VideoWriter('test.avi',fourcc,24,(int(width),int(height)))

while cap.isOpened():
    # 카메라 프레임 읽기
    success, frame = cap.read()
    if success:
        writer.write(frame) # 프레임 저장
        cv2.imshow('Video Window',frame)

        key = cv2.waitKey(1) & 0xFF == ord('q')
        if key == 27:
            break
    else:
        break

cap.release()
writer.release()
cv2.destroyAllWindows()
