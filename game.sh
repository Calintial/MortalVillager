if [[ $1 -eq "1" ]]; then
	make pathfinding
elif [[ $1 -eq "1" ]]; then
	make ia
else
	make
fi

# Si make ha funcionado:
if [ $? -eq 0 ] ; then
	
	cd bin/
	if [[ $1 -eq "1" ]]; then
		./pathfinding
	elif [[ $1 -eq "2" ]]; then
		./ia_batalla
	else
		./main
	fi
	cd ..
fi