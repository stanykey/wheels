#!/bin/sh

pip3 install --upgrade pre-commit
pre-commit install --install-hooks --overwrite
