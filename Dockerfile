FROM quanteek/vle:1.1.2
MAINTAINER quanteek

#create project
USER user01
WORKDIR /home/user01
RUN vle -P lotka-volterra create

#copy cpp
COPY SystemLotkaVolterra.cpp /home/user01/lotka-volterra/src/
WORKDIR /home/user01/lotka-volterra/src/
RUN sed -i.bak "s/Simple/SystemLotkaVolterra/g" CMakeLists.txt

#copy vpz
COPY empty.vpz /home/user01/lotka-volterra/exp/

#configure and build project
WORKDIR /home/user01
RUN vle -P lotka-volterra configure build || vle -P lotka-volterra configure build

#copy simulator
COPY run.sh /home/user01/

