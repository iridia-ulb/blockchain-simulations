#!/bin/bash
# Iterate over experimental settings and start experiments
source experimentconfig.sh
DATAFOLDER="$EXPERIMENTFOLDER/results/data"

##################################################################################
### EXAMPLE: config "NUMROBOTS" 10 
config() {
	sed -i "s|^export ${1}=.*|export ${1}=${2}|" experimentconfig.sh
}

##################################################################################
### EXAMPLE: loopconfig "patches" "radius" 0.05 
loopconfig() {
	sed -i "/\['${1}'\]\['${2}'\]/ s/=.*/= ${3}/" loop_functions/loop_params.py
}

##################################################################################
### EXAMPLE: copy "test116_patchy/20_blockchain1"
copy() {
	# Collect the config from results
	cp $DATAFOLDER/experiment_${1}/001/experimentconfig.sh .
	cp $DATAFOLDER/experiment_${1}/001/controller_params.py controllers/
	cp $DATAFOLDER/experiment_${1}/001/loop_function_params.py loop_functions/
}

##################################################################################
### EXAMPLE: import "test116_patchy/20_blockchain1"
import() {
	# Collect the config from results
	SSHHOST="eksander@esme"
	SSHSOCKET=~/.ssh/$SSHHOST
	
	ssh -M -f -N -o ControlPath=$SSHSOCKET $SSHHOST
	scp -o ControlPath=$SSHSOCKET $SSHHOST:$DATAFOLDER/experiment_${1}/001/experimentconfig.sh .
	scp -o ControlPath=$SSHSOCKET $SSHHOST:$DATAFOLDER/experiment_${1}/001/controller_params.py controllers/
	scp -o ControlPath=$SSHSOCKET $SSHHOST:$DATAFOLDER/experiment_${1}/001/loop_function_params.py loop_functions/
	ssh -S $SSHSOCKET -O exit $SSHHOST
}

##################################################################################
### EXAMPLE: run "test116_patchy/20_blockchain1"
run() {

	# Configure experiment
	. experimentconfig.sh

	# If is a testrun
	if  [[ $2 = "--test" || $2 = "-t" ]]; then
		echo "Running test ${1}"
		. starter -r -s
		    bash collect-logs ${1}
	elif [[ $2 = "--no-blockchain" || $2 = "-n" ]]; then
		echo "Running blockchain free test ${1}"
		. starter -s
	else
		for REP in $(seq 1 ${REPS}); do
			echo "Runing experiment ${1}"

			# Perform experiment
			. starter -r -sz

			# Collect data
			if [ $# -eq 1 ]; then
			    bash collect-logs ${1}
			fi
			
		done
	fi
}



EXP=G1
config "REPS" 20
config "NUM1" 24
config "FLOORFILE" 38.png
config "ARENADIM" 1.9
config "ARENADIMH" 0.95
config "RABRANGE" 0.13
config "NOTES" "\"Experiment 1 in the Science Robotics paper (24 robots with an increasing number of Byzantines)\""
config "REALTIME" "true"


for NUMBYZANTINE in 0 3 6 9; do
    CFG=24rob-${NUMBYZANTINE}byz
    config "NUMBYZANTINE" ${NUMBYZANTINE}
    wait
    run "${EXP}/${CFG}" $1
done
