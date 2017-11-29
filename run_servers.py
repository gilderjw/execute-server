#!/usr/bin/python

import subprocess

def main(path='server.conf'):
  file = open(path)
  entries = map(lambda x: x.strip().split(':'), file.readlines())

  for (exe_path, port) in entries:
    subprocess.Popen(["./server", exe_path, port])


if __name__ == '__main__':
  main()