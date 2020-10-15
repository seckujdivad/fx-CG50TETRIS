import os
import shutil
import json


if not os.path.exists(".vscode/scriptsettings.json"):
    print("No config file found, creating with default settings...")
    shutil.copyfile(".vscode/scriptsettings-sample.json", ".vscode/scriptsettings.json")

with open(".vscode/scriptsettings.json", "r") as file:
    config = json.load(file)

if os.path.exists(config["filename"]):
    os.rename(config["filename"], "__" + config["filename"])

print("Building...")
os.system("make")

if os.path.exists(config["filename"]):
    print("Build was successful")

    if os.path.exists("__" + config["filename"]):
        os.remove("__" + config["filename"])

    if os.path.exists(config["destination"]):
        shutil.copyfile(config["filename"], os.path.join(config["destination"], config["filename"]))
        print("Move was successful")
    else:
        print("Drive not inserted, move not attempted")

else:
    print("Build was unsuccessful, move not attempted")

    if os.path.exists("__" + config["filename"]):
        os.rename("__" + config["filename"], config["filename"])