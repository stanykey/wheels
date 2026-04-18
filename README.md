# Wheels

This is my little C++ utility library where I usually :
- try to re-invent the wheels to get a better understanding of how it works
- implement things I've watched/heard at some meetings/events/videos
- try to meet the [CppCoreGuidelines](https://github.com/isocpp/CppCoreGuidelines) requirements
- last but not least, take the fun with C++

---

### Pre-commit hooks
Requirements:
- Python 3
- pre-commit package

Optionally you can create virtual environment:

Windows:
```shell
python -m venv .venv
.venv/Scripts/activate.bat
```

Linux:
```shell
python3 -m venv .venv
source .venv/bin/activate
```

Install hooks:
```shell
pip intall --upgrate pre-commit
pre-commit install --color=always --overwrite
```
