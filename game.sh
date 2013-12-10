if [[ $1 -eq "1" ]]; then
	make pathfinding
else
	make
fi

# Si make ha funcionado:
if [ $? -eq 0 ] ; then
	
	cd bin/
	if [[ $1 -eq "1" ]]; then
		./pathfinding
	else
		./main
	fi
	cd ..
fi