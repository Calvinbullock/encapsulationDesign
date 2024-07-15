# FOR GUI compile
# make 
# ./runMe
# make clean

# testing no gui
make -f makeMain
echo "--------------------------------------------------"
./runMe
echo "--------------------------------------------------"
rm runMe
#make -f makeMain clean
