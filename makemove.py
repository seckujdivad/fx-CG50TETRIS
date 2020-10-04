import os
import shutil


os.system("make")

if os.path.exists("E:"):
    shutil.copyfile("fx-CG50TETRIS.g3a", "E:/fx-CG50TETRIS.g3a")
    print("Move was successful")
else:
    print("Drive not inserted, move not attempted")