# name			: 42/Norminette Markers
# description	: Run the norminette
# onSave		: *.[ch]{1}$

import re

loadModule('/System/Environment');
loadModule('/System/Resources');
loadModule('/System/UI');
loadModule('/System/Platform');
loadModule('/System/JVM');

DEBUG = False
EXECUTABLE = "norminette"
OUT_FORMAT = "{head: <5} | {line: >4} | {column: >3} | {error}"

class NorminetteError:

	def __init__(self, context, message):
		self.context = context
		self.message = message
		
	def __str__(self):
		return "NorminetteError[context={}, error={}]".format(self.context, self.message)
	
	def extract_line(self):
		if (self.context == None):
			return 0
		for match in re.finditer(r"line ([\d]+)", self.context, re.MULTILINE):
			return int(match.group(1));
		return 0
	
	def extract_column(self):
		if (self.context == None):
			return ""
		for match in re.finditer(r"col ([\d]+)", self.context, re.MULTILINE):
			return int(match.group(1));
		return ""
	
	@staticmethod
	def create(context, message):
		context = context.strip()
		message = message.strip()
		if context == "":
			context = None
		return NorminetteError(context, message)


class Norminette:
	
	def initialize(self):
		self.workspace_file = argv[0]
		self.workspace_path = str(org.eclipse.core.resources.ResourcesPlugin.getWorkspace().getRoot().getLocation())
		self.absolute_file = self.workspace_path + "/" + self.workspace_file.replace("workspace://", "")
		self.resource_file = None

		for file in findFiles("*.[chpy]$", "workspace://"):
			if (str(file.getLocation()) == self.absolute_file):
				self.resource_file = file
				break
		
		if (self.resource_file == None):
			self.exit("No Eclipse corresponding resource found.")
			
		if DEBUG:
			self.dump_properties()
	
	def dump_properties(self):
		print("")
		print("Properties")
		print("  WORKSPACE	: " + self.workspace_path)
		print("  (WS) FILE	: " + self.workspace_file)
		print("  (CC) FILE	: " + self.absolute_file)
		print("  RESOURCE	: " + str(self.resource_file))
		print("")
	
	def delete_old_markers(self):
		self.resource_file.deleteMarkers(org.eclipse.core.resources.IMarker.PROBLEM, True, org.eclipse.core.resources.IResource.DEPTH_INFINITE)
	
	def launch_process(self):
		process = runProcess(EXECUTABLE, [self.absolute_file])
		reader = java.io.BufferedReader(java.io.InputStreamReader(process.getInputStream()));
		lines = ""
		while True:
			line = reader.readLine()
			if line == None:
				break
			lines += line + "\n"
		return lines
	
	def find_errors(self):
		lines = self.launch_process()
		matches = re.finditer(r"Error(.*?):(.*?$)", lines, re.MULTILINE)

		errors = []
		for match in matches:
			errors.append(NorminetteError.create(match.group(1), match.group(2)))
		return errors
	
	def work(self):
		self.delete_old_markers()
		print("Resource: " + self.absolute_file)
		
		errors = self.find_errors()
		
		if len(errors) == 0:
			print("Everything is good!")
			return
		print(OUT_FORMAT.format(head="ERROR", line="LINE", column="COL", error="ERROR"))
		
		for error in errors:
			severity = "WARNING"
			target_file = self.workspace_file
			line = error.extract_line()
			column = error.extract_column()
			message = error.message
			
			if error.message == "":
				continue
			
			createProblemMarker(severity, target_file, line, "[norminette] {}".format(message), permanent=False)

			if error.context == None:
				line = ""
				column = ""
			print(OUT_FORMAT.format(head="", line=line, column=column, error=message))
	
	def exit(self, reason=None):
		if (reason != None):
			print(reason)
		exit()

print("Norminette Markers by Enzo Caceres")

app = Norminette()
app.initialize()
app.work()