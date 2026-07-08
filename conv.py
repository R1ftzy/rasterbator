import os
from PIL import Image

for file in os.listdir("."):
    if file.endswith(".ppm"):
        img = Image.open(file)
        img.save(file.replace(".ppm", ".png"))