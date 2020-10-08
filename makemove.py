import os
import shutil


filename = "fx-CG50TETRIS.g3a"

os.rename(filename, "__" + filename)

os.system("make")

if os.path.exists("fx-CG50TETRIS.g3a"):
    print("Build was successful")
    os.remove("__" + filename)

    if os.path.exists("E:"):
        shutil.copyfile("fx-CG50TETRIS.g3a", "E:/fx-CG50TETRIS.g3a")
        print("Move was successful")
    else:
        print("Drive not inserted, move not attempted")

else:
    print("Build was unsuccessful, move not attempted")

    os.rename("__" + filename, filename)