CFLAGS = -std=c++17 -I/opt/homebrew/include -I/Users/andreitrcv/Documents/2D_GameEngine/ECS

LDFLAGS = -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf

a.out: *.cpp ECS/*.cpp *.h
	g++ $(CFLAGS) -o a.out *.cpp ECS/*.cpp $(LDFLAGS)

.PHONY: test clean

test: a.out
	./a.out

clean:
	rm -f a.out
	


