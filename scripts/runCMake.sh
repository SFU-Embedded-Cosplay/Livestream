startRed=`tput setaf 1`
endColorChange=`tput sgr0`
echo "${startRed}make sure you ran this script from inside the scripts directory.${endColorChange}"

cd ..
mkdir build
cd build
cmake ./ ../
