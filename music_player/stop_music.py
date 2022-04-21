import pygame
import os

# pid를 읽어올 파일 path를 저장한다
file_path = "/home/pi/id_saver.txt"

# read 모드로 파일을 열고 적혀 있는 pid를 읽는다
f = open(file_path, "r")
s = f.readline()

# 해당 process id에 맞는 프로세스를 kill(노래 종료)
os.system("fg")
os.system("kill " + s)

# 해당 id_saver 파일 제거
os.system("rm -rf " + file_path)