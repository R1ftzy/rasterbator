from pathlib import Path

for ext in ("*.ppm", "*.png"):
    for file in Path(".").rglob(ext):
        file.unlink()
        print(f"Deleted {file}")