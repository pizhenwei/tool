#!/usr/bin/python2.7

import sys, getopt

def generate_data_for_excel(parafile, datafile, mode, outputfile):
	paras = []
	try:
		with open(parafile, 'r') as f:
			for line in f.readlines():
				line = line[:len(line)-1]
				paras.append(line)
		f.close()
		#print paras

	except Exception, e:
		print e

	data_count = 0
	data_lines = []
	try:
		lines = 0
		with open(datafile, 'r') as f:
			for line in f.readlines():
				line = line[:len(line)-1]
				data_lines.append(line)
				lines += 1
		f.close()
		data_count = lines / len(paras)
		print "total para : lines = %d" % len(paras)
		print "total data : lines = %d" % lines

	except Exception, e:
		print e


	try:
		with open(outputfile, 'w') as f:
			for index in range(len(paras)) :
				outstr = ""
				outstr += paras[index]
				outstr += "|"
				if mode == "inc" :
					c = 1
					while (c < data_count) :
						outstr += (str(int(data_lines[index + c * len(paras)]) \
							- int(data_lines[index + (c-1) * len(paras)]))+ "|")
						c += 1
				else :
					for c in range(data_count) :
						outstr += ((data_lines[index + c * len(paras)]) + "|")
				outstr += "\n"
				#print outstr
				f.write(outstr)
		f.close()

	except Exception, e:
		print e


def parse_arg(argv):
	parafile = ''
	datafile = ''
	mode = ''
	try:
		opts, args = getopt.getopt(argv,"hp:d:m:",["para=","data=","mode="])
	except getopt.GetoptError:
		print 'test.py -p <para> -o <data>'
		sys.exit(2)

	for opt, arg in opts:
		if opt == '-h':
			print 'test.py -p <para> -d <data> -m <inc>'
			sys.exit()
		elif opt in ("-p", "--para"):
			parafile = arg
		elif opt in ("-d", "--data"):
			datafile = arg
		elif opt in ("-m", "--mode"):
			mode = arg

	return parafile, datafile, mode

if __name__ == "__main__":
	parafile = ''
	datafile = ''
	parafile, datafile, mode = parse_arg(sys.argv[1:])
	#print 'para file is ', parafile
	#print 'data file is ', datafile
	if parse_arg == '' or datafile == '':
		print sys.argv[0] + ' -p <para> -d <data>'

	generate_data_for_excel(parafile, datafile, mode, "output.txt")
