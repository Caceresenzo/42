glew:
	rm -rf /tmp/glew
	git clone https://github.com/nigels-com/glew.git /tmp/glew
	cd /tmp/glew/auto && make
	cd /tmp/glew && make
	mkdir glew
	cp -r /tmp/glew/bin/* /tmp/glew/lib/* /tmp/glew/includes/* glew

