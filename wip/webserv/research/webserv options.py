struct Option {
	char		short;
	string		long;
	bool		hasValue;
	string		description;
	
	string		value;
}

list<Option> opts;

Option fOpt = Option(short='f', long="file", hasValue=True, description="Specify the F argument")
Option aOpt = Option(short='a', long="all", hasValue=False, description="Specify the A argument")
Option helpOpt = Option(short='h', long="help", hasValue=False, description="Help message")

opts.add(fOpt)
opts.add(aOpt)
opts.add(helpOpt)

./webserv -f Hello -h -a

f=Hello
h=
a=

Parser parser = Parser(ops)
map<short, value>

for arg in [ "-h" ]:
	for opt in opts:
		if opt.short == arg:
			map[opt.short] = "";
			
			if opt.hasValue:
				if (map[opt.short] = next(arg)) == NULL:
					raise OptionParseException("Option -" + opt.short + " expected a value")
				
			
			break


if parser.hasOption(helpOpt):
	parser.printHelp()
	exit()
	
file = "./config.json"
if parser.hasOption(fOpt):
	file = parser.getOptionValue(fOpt)
	

for opt in opts:
	print(opt.short + opt.long + opt.desc)
