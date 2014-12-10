INCLUDE = -I/usr/X11R6/include/
LIBDIR  = -L/usr/X11R6/lib

COMPILERFLAGS = -Wall -g
CC = g++
CXXFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lglut -lGL -lGLU -lm

game: main.cpp Vector.o Terrain.o Entity.o Vehicle.o Turret.o Armament.o Bullet.o Controller.o Entity3D.o Terrain3D.o Turret3D.o Vehicle3D.o Bullet3D.o Object3D.o Explosion3D.o tgautils.o LightPanel.o FogPanel.o DisplayListPanel.o
	$(CC) $(CXXFLAGS) main.cpp Vector.o Terrain.o Entity.o Vehicle.o Turret.o Armament.o Bullet.o Controller.o Entity3D.o Terrain3D.o Turret3D.o Vehicle3D.o Bullet3D.o Object3D.o Explosion3D.o tgautils.o LightPanel.o FogPanel.o DisplayListPanel.o -o game $(LIBDIR) $(LIBRARIES)

Vector.o: Vector.cpp Vector.h
	$(CC) $(CXXFLAGS) -c Vector.cpp -o Vector.o

Terrain.o: Terrain.cpp Terrain.h
	$(CC) $(CXXFLAGS) -c Terrain.cpp -o Terrain.o

Entity.o: Entity.cpp Entity.h Vector.o
	$(CC) $(CXXFLAGS) -c Entity.cpp -o Entity.o

Vehicle.o: Vehicle.cpp Vehicle.h
	$(CC) $(CXXFLAGS) -c Vehicle.cpp -o Vehicle.o

Turret.o: Turret.cpp Turret.h
	$(CC) $(CXXFLAGS) -c Turret.cpp -o Turret.o

Armament.o: Armament.cpp Armament.h
	$(CC) $(CXXFLAGS) -c Armament.cpp -o Armament.o

Bullet.o: Bullet.cpp Bullet.h
	$(CC) $(CXXFLAGS) -c Bullet.cpp -o Bullet.o

Controller.o: Controller.cpp Controller.h
	$(CC) $(CXXFLAGS) -c Controller.cpp -o Controller.o

Entity3D.o: Entity3D.cpp Entity3D.h
	$(CC) $(CXXFLAGS) -c Entity3D.cpp -o Entity3D.o

Terrain3D.o: Terrain3D.cpp Terrain3D.h
	$(CC) $(CXXFLAGS) -c Terrain3D.cpp -o Terrain3D.o

Turret3D.o: Turret3D.cpp Turret3D.h
	$(CC) $(CXXFLAGS) -c Turret3D.cpp -o Turret3D.o

Vehicle3D.o: Vehicle3D.cpp Vehicle3D.h
	$(CC) $(CXXFLAGS) -c Vehicle3D.cpp -o Vehicle3D.o

Bullet3D.o: Bullet3D.cpp Bullet3D.h
	$(CC) $(CXXFLAGS) -c Bullet3D.cpp -o Bullet3D.o

Object3D.o: Object3D.cpp Object3D.h
	$(CC) $(CXXFLAGS) -c Object3D.cpp -o Object3D.o

Explosion3D.o: Explosion3D.cpp Explosion3D.h
	$(CC) $(CXXFLAGS) -c Explosion3D.cpp -o Explosion3D.o

tgautils.o: tgautils.c tgautils.h
	$(CC) $(CXXFLAGS) -c tgautils.c -o tgautils.o

LightPanel.o: LightPanel.cpp LightPanel.h
	$(CC) $(CXXFLAGS) -c LightPanel.cpp -o LightPanel.o

FogPanel.o: FogPanel.cpp FogPanel.h
	$(CC) $(CXXFLAGS) -c FogPanel.cpp -o FogPanel.o

DisplayListPanel.o: DisplayListPanel.cpp DisplayListPanel.h
	$(CC) $(CXXFLAGS) -c DisplayListPanel.cpp -o DisplayListPanel.o

clean:
	rm *.o game

