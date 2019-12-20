1) setup leapmotion on archlinux
	yaourt -S leap-motion-driver
2) to run leap 
	sudo systemctl start leapd.service (or) sudo leapd &!
3) To open leap control panel
	LeapControlPanel
4) to setup a project
	git clone https://github.com/ramkalath/Leapmotion_Modern_opengl_visualizer
5) cd into the project and type
	make
	make run
