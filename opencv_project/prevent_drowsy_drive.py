# import the necessary packages
from scipy.spatial import distance as dist # 유클리디안 공식을 통한 거리 측정
from imutils.video import VideoStream # Pi camera 접근 허용(성능 좋음)
from imutils import face_utils
from threading import Thread
import numpy as np
# import playsound # for windows
import datetime
import argparse
import imutils
import time
import dlib
import cv2

# make alarm to wake the driver
def sound_alarm(path):
    # play an alarm sound
    # maybe we can use pygame.
    pass

def eye_aspect_ratio(eye):
	# compute the euclidean distances between the two sets of
	# vertical eye landmarks (x, y)-coordinates

    # 눈을 기준으로 왼쪽 끝이 0번 index고, 시계 방향으로 회전하면서 증가

    A = dist.euclidean(eye[1],eye[5])
    B = dist.euclidean(eye[2],eye[4])

	# compute the euclidean distance between the horizontal
	# eye landmark (x, y)-coordinates
    C = dist.euclidean(eye[0],eye[3])

    # EAR 알고리즘을 활용한 졸음 인식
    # EAR = |p2 - p6| + |p3 - p5| / 2 * |p1 - p4|
    ear = (A + B) / (2.0 * C)

    return ear

