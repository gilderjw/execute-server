#!/usr/bin/python

import os
import sys
import subprocess

def main(path='server.conf'):
  dir_path = os.getcwd()
  file = open(path)

  # parse list of entries
  entries = map(lambda x: x.strip().split(':'), file.readlines())

  for (exe_path, port, working_dir) in entries:
    print('starting ' + exe_path + ' on port ' + port + '\n')

    exe_path = os.path.join(os.path.abspath(sys.path[0]), exe_path)
    working_dir = os.path.join(os.path.abspath(sys.path[0]), working_dir)

    # launch server with given working directory
    os.chdir(working_dir)
    subprocess.Popen([dir_path + "/server", exe_path, port])
    os.chdir(dir_path)

if __name__ == '__main__':
  main()


