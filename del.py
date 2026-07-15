from pathlib import Path

for ext in ("*.ppm", "*.png"):
    for file in Path(".").rglob(ext):
        if any(part.lower() == "assets" for part in file.parts):
            continue
        try:
            file.unlink()
            print(f"Deleted {file}")
        except Exception as e:
            print(f"Failed to delete {file}: {e}")