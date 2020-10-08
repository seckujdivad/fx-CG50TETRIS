import os
import shutil


def safe_remove(path):
	if os.path.exists(path):
		os.remove(path)


safe_remove("fx-CG50TETRIS.bin")
safe_remove("fx-CG50TETRIS.g3a")
safe_remove("__fx-CG50TETRIS.g3a")

for filename in os.listdir("build"):
	safe_remove(os.path.join("build", filename))