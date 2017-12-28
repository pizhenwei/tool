#!/usr/bin/python
import os
import sys
import getopt
import commands
import httplib
import json

forlder = "changelogs"

def get_one(url):
	s = url.split("/")
	file_name =  forlder + "/" + s[-1]
	gz_name =  forlder + "/" + s[-1] + ".gz"
	print file_name

	cmd = "curl " + url + " -o " + gz_name
	os.system(cmd);

	cmd = "gunzip " + gz_name
	os.system(cmd);

	cmd = "mv " + gz_name + " " + file_name
	os.system(cmd);

if __name__=="__main__":
	cmd = "mkdir -p " + forlder
	os.system(cmd);

	for n in range(69, 109) :
		url = "https://cdn.kernel.org/pub/linux/kernel/v4.x/ChangeLog-4.4." + str(n)
		get_one(url)

	print "done !"
