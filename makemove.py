import os
import shutil


filename = "fx-CG50TETRIS.g3a"

if os.path.exists(filename):
    os.rename(filename, "__" + filename)

os.system("make")

if os.path.exists(filename):
    print("Build was successful")

    if os.path.exists("__" + filename):
        os.remove("__" + filename)

    if os.path.exists("E:"):
        shutil.copyfile(filename, os.path.join("E:", filename))
        print("Move was successful")
    else:
        print("Drive not inserted, move not attempted")

else:
    print("Build was unsuccessful, move not attempted")

    if os.path.exists("__" + filename):
        os.rename("__" + filename, filename)