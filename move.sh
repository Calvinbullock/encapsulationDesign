lastWeek="5week"
thisWeek="6week"

cp -i ./$lastWeek/acceleration.cpp ./$thisWeek/acceleration.cpp 
cp ./$lastWeek/acceleration.h ./$thisWeek/acceleration.h

cp ./$lastWeek/angle.cpp ./$thisWeek/angle.cpp
cp ./$lastWeek/angle.h ./$thisWeek/angle.h

cp ./$lastWeek/position.cpp ./$thisWeek/position.cpp
cp ./$lastWeek/position.h ./$thisWeek/position.h

cp ./$lastWeek/velocity.cpp ./$thisWeek/velocity.cpp
cp ./$lastWeek/velocity.h ./$thisWeek/velocity.h

cp ./$lastWeek/lander.cpp ./$thisWeek/lander.cpp
cp ./$lastWeek/lander.h ./$thisWeek/lander.h

# header(only) files
cp ./$lastWeek/simulator.cpp ./$thisWeek/simulator.cpp
cp ./$lastWeek/star.h ./$thisWeek/star.h
cp ./$lastWeek/thrust.h ./$thisWeek/thrust.h

# compile files
cp ./$lastWeek/makefile ./$thisWeek/makefile
cp ./$lastWeek/guiRun.sh ./$thisWeek/guiRun.sh

