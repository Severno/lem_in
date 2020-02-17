#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

cols=$(tput cols)
numcols=$(((cols-10)/2))

function press_key {
	echo "${RED}"
	read -n 1 -s -p "Press any key to continue"
	printf "\n"
	echo "${NC}"
}

if [ ! -f lem-in ]
then make
fi

clear
tput cup 0 $numcols
echo "LEM-IN GRADING"
press_key
echo "${GREEN}Lecture sur l'entree standard${NC}"
echo "See script or test it"
press_key
echo "${GREEN}Tests d'erreurs - Aucune Salle${NC}"
echo "No Rooms"
./lem-in < maps/error_18_no_room.map
press_key
echo "${GREEN}Tests d'erreurs - Aucune Fourmi${NC}"
echo "No Ants"
./lem-in < maps/error_8_no_hex.map
press_key
echo "${GREEN}Tests d'erreurs - Aucun Commentaire Obligatoire${NC}"
echo "No Start"
./lem-in < maps/error_10_no_start.map
press_key
echo "${GREEN}Tests d'erreurs - Aucun Chemin Possible${NC}"
echo "No Path"
./lem-in < maps/error_9_no_path.map
press_key
echo "${GREEN}Tests d'erreurs - Commandes et Commentaires${NC}"
echo "Comment"
./lem-in < maps/sujet_7_comment.map
press_key
echo "${GREEN}Tests d'erreurs - Chemin des Fourmis${NC}"
echo "Direct Start to End"
./lem-in < maps/sujet_4_direct_start_to_end.map
press_key
echo "${GREEN}Tests d'erreurs${NC}"
echo "Empty Line in file"
./lem-in < maps/error_0_empty_line.map
press_key
echo "* in File"
./lem-in < maps/error_11_other_char.map
press_key
echo "Rooms After Tubes"
./lem-in < maps/error_12_room_after_tube.map
press_key
echo "Room in Tubes Part"
./lem-in < maps/error_13_room_in_tube.map
press_key
echo "Tubes Before Rooms"
./lem-in < maps/error_14_tube_before_room.map
press_key
echo "Tube in Room Part of File"
./lem-in < maps/error_15_tube_in_room.map
press_key
echo "Name Room Start With L"
./lem-in < maps/error_16_room_start_L.map
press_key
echo "Name Room Start With #"
./lem-in < maps/error_17_room_start_#.map
press_key
echo "No Tube"
./lem-in < maps/error_19_no_tube.map
press_key
echo "First Empty Line"
./lem-in < maps/error_1_first_empty_line.map
press_key
echo "Number of - in File"
./lem-in < maps/error_20_numbers-of-minus.map
press_key
echo "Number of Spaces in File"
./lem-in < maps/error_21_numbers-of-space.map
press_key
echo "Float"
./lem-in < maps/error_2_float.map
press_key
echo "Format Room"
./lem-in < maps/error_3_format_room.map
press_key
echo "Format Tube"
./lem-in < maps/error_4_format_tube.map
press_key
echo "Format Separator Room"
./lem-in < maps/error_5_format_separator_room.map
press_key
echo "Format Separator Tube"
./lem-in < maps/error_6_format_separator_tube.map
press_key
echo "No End"
./lem-in < maps/error_7_no_end.map
press_key
echo "Rooms Same Name"
./lem-in < maps/sujet_0_inline.map
press_key
echo "Tube Between Rooms That Doesn't Exists"
./lem-in < maps/sujet_10_bad_tube.map
press_key
echo "Unknown Command"
./lem-in < maps/sujet_11_unknown_command.map
press_key
echo "Equal Paths"
./lem-in < maps/sujet_1_2_equals_pathes.map
press_key
echo "Rooms Same Name"
./lem-in < maps/sujet_2_8_rooms.map
press_key
echo "Equal Paths"
./lem-in < maps/sujet_3_2_equals_pathes.map
press_key
echo "Name Room"
./lem-in < maps/sujet_5_to_big_and_to_short_path.map
press_key
echo "Empty Line in file"
./lem-in < maps/sujet_6_empty_line.map
press_key
echo "Tube With a Room That Doesn't Exist"
./lem-in < maps/sujet_8_tube_with_inexistent_room.map
press_key
echo "Rooms With Same Coordinates"
./lem-in < maps/sujet_9_tube_with_inexistent_tube.map
press_key
echo "${GREEN}Justesse de l'algo - Validite du Chemin${NC}"
echo "1000 rooms"
press_key
./lem-in < maps/1000.map
press_key
echo "${GREEN}BONUS - Usage${NC}"
echo "./lem-in -h < maps/1000.map"
./lem-in -h < maps/1000.map
press_key
echo "${GREEN}BONUS - Print Path${NC}"
echo "./lem-in -p < maps/1000.map"
press_key
./lem-in -p < maps/1000.map
press_key
echo "${GREEN}BONUS - Nombre de Fourmi${NC}"
echo "./lem-in -H10 < maps/1000.map"
press_key
./lem-in -H10 < maps/1000.map