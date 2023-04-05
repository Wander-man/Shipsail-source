PROG = Shipsail.exe
CC = g++

CPPFLAGS = -g -I.\include -ID:\projs\SFML\SFML-2.5.1\include -DSFML_STATIC
LDLIBS   := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s
LDLIBS   += -lopengl32 -lwinmm -lgdi32 -lstdc++ -lfreetype -mwindows #kill console
LDFLAGS = --static -static-libgcc -LD:\projs\SFML\SFML-2.5.1\lib 

OFILES = main.o game.o gamemap.o obj_map.o astar.o icashe.o obj_enemy_sship.o obj_enemy_armship.o obj_aenemy.o obj_projectile.o strndef.o ui_button.o ui_tlabel.o ui_textbar.o w_logwindow.o w_awindow.o w_menuwindow.o obj_atower.o obj_tower_1.o obj_tower_2.o obj_tower_3.o ui_counter.o g_stats.o

all: $(PROG)

$(PROG): $(OFILES)
	$(CC) -o $(PROG) $(OFILES) $(LDFLAGS) $(LDLIBS)

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp 

game.o: game.cpp
	$(CC) $(CPPFLAGS) -c game.cpp 

gamemap.o: gamemap.cpp
	$(CC) $(CPPFLAGS) -c gamemap.cpp 

obj_map.o: obj_map.cpp icashe.cpp
	$(CC) $(CPPFLAGS) -c obj_map.cpp 

obj_enemy_sship.o: obj_enemy_sship.cpp obj_aenemy.o
	$(CC) $(CPPFLAGS) -c obj_enemy_sship.cpp 

obj_enemy_armship.o: obj_enemy_armship.cpp obj_aenemy.o
	$(CC) $(CPPFLAGS) -c obj_enemy_armship.cpp 

obj_aenemy.o: obj_aenemy.cpp strndef.o
	$(CC) $(CPPFLAGS) -c obj_aenemy.cpp

astar.o: astar.cpp
	$(CC) $(CPPFLAGS) -c astar.cpp
	
icashe.o: icashe.cpp
	$(CC) $(CPPFLAGS) -c icashe.cpp

strndef.o: strndef.cpp
	$(CC) $(CPPFLAGS) -c strndef.cpp
	
ui_button.o: ui_button.cpp
	$(CC) $(CPPFLAGS) -c ui_button.cpp	

ui_tlabel.o: ui_tlabel.cpp
	$(CC) $(CPPFLAGS) -c ui_tlabel.cpp

ui_textbar.o: ui_textbar.cpp ui_button.o ui_tlabel.o
	$(CC) $(CPPFLAGS) -c ui_textbar.cpp
	
ui_counter.o: ui_counter.cpp ui_tlabel.o
	$(CC) $(CPPFLAGS) -c ui_counter.cpp

w_awindow.o: w_awindow.cpp ui_textbar.o ui_button.o
	$(CC) $(CPPFLAGS) -c w_awindow.cpp

w_logwindow.o: w_logwindow.cpp w_awindow.o
	$(CC) $(CPPFLAGS) -c w_logwindow.cpp

w_menuwindow.o: w_menuwindow.cpp w_awindow.o
	$(CC) $(CPPFLAGS) -c w_menuwindow.cpp

obj_projectile.o: obj_projectile.cpp
	$(CC) $(CPPFLAGS) -c obj_projectile.cpp

obj_atower.o: obj_atower.cpp obj_projectile.o obj_aenemy.o
	$(CC) $(CPPFLAGS) -c obj_atower.cpp

obj_tower_1.o: obj_tower_1.cpp obj_atower.o 
	$(CC) $(CPPFLAGS) -c obj_tower_1.cpp

obj_tower_2.o: obj_tower_2.cpp obj_atower.o 
	$(CC) $(CPPFLAGS) -c obj_tower_2.cpp

obj_tower_3.o: obj_tower_3.cpp obj_atower.o 
	$(CC) $(CPPFLAGS) -c obj_tower_3.cpp

g_stats.o: g_stats.cpp
	$(CC) $(CPPFLAGS) -c g_stats.cpp

clean:
	del $(OFILES)
