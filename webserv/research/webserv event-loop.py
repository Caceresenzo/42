list<Server> servers
list<FileDescriptorWrapper> readFileFds
list<FileDescriptorWrapper> writeFileFds
list<Client> clients

while True:
	select()
	
	# Server socket :: accept()
	for server in servers:
		server.accept();
	
	# Files (read) :: read()
	for file in readFileFds:
		file.fillWithRead()
		
	# Client sockets :: recv(), send()
	for client in clients:
		if not client.hasHeader():
			client.fd.fillWithRecv()
			
			for c in client.fd.consume():
				if client.parseHeader(c):
					# ^^^ Server and route matching
					# ^^^ Method handling
					break
		else if not client.hasResponse():
			if client.header.hasBody():
				client.fd.fillWithRecv()
				
				# TODO: Handle compression
		else
			if client.fd.flushWithSend():
				readFileFds.remove(client.getReadFile())
				writeFileFds.remove(client.getWriteFile())
			
				clients.remove(client)
	
	# Files (write) :: write()
	for file in writeFileFds:
		file.flushWithWrite()