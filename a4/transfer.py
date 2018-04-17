#!/usr/bin/env python2.7
import os

os.system("scp -P 2222 ./*.py parallel@localhost:~/")
#os.system("scp -P 2222 ./*.java parallel@localhost:~/")
