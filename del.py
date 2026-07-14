from pathlib import Path

for ext in ("*.ppm", "*.png"):
    for file in Path(".").rglob(ext):
        if "assets" in file.parts:
            continue
        file.unlink()
        print(f"Deleted {file}")