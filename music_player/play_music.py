import pygame
import os

# 절대 경로를 통해 현재 재생중인 음악이 있다면 멈춘다
os.system("python /home/pi/webapps/music_play/stop_music.py")

# 절대 경로를 통해 현재 플레이리스트에 저장 되어 있는 음악들을 list 형태로 가져온다
path = "/home/pi/music_list/"
music_list = os.listdir(path)

# 음악 플레이를 위한 mixer init
pygame.mixer.init()

# music_list에 있는 음악들을 순차적으로 재생
for music in music_list:
    # 백그라운드 재생을 위한 설정
    # 프로세스 id를 저장하기 위한 file control
    file_path = "/home/pi/id_saver.txt"

    # pygame.mixer 설정
    pygame.mixer.music.set_volume(0.1)
    pygame.mixer.music.load(path + music)
    pygame.mixer.music.play()

    # file을 쓰기 모드로 열고 백그라운드 재생 중인 프로세스의 id를 저장한다
    f = open(file_path,"w")
    f.write(str(os.getpid()))
    f.close()

    # 인스턴스로 메모리에 파일을 한 번에 로드해서 실행하는 것이 아니라
    # 스트리밍 형식으로 파일을 실시간으로 로드 하면서 처리한다
    while pygame.mixer.music.get_busy() == True:
        continue

