lab1:
	acom -std=c99 -Ilib labs/lab1.c lib/D3d_matrix_student.c -o bin/lab1

lab2:
	acom -std=c99 -Ilib labs/lab2.c lib/D3d_matrix_student.c lib/vectors.c lib/light_model_student.c -o bin/lab2

lab2-movie: lab2 movieplayer
	labs/lab2-par.sh && printf "lab2-mov\n0\n30\n" | bin/movieplayer

lab2.1:
	acom -std=c99 -Ilib labs/lab2.1.c lib/D3d_matrix_student.c lib/vectors.c lib/light_model_student.c -o bin/lab2.1

final-project:
	acom -std=c99 -Ilib labs/final-project.c lib/D3d_matrix_student.c lib/vectors.c lib/light_model_student.c -o bin/final-project

frames=10
lab2.1-movie: lab2.1 movieplayer
	labs/lab2.1-par.sh $(frames) && printf "lab21-mov\n0\n$(frames)\n" | bin/movieplayer

lab3:
	acom -std=c99 -Ilib labs/lab3.c lib/D3d_matrix_student.c lib/vectors.c lib/light_model_student.c -o bin/lab3

raytrace-test:
	acom -std=c99 -Ilib labs/raytrace-test.c lib/D3d_matrix_student.c lib/vectors.c lib/light_model_student.c -o bin/raytrace-test

movieplayer:
	acom examples/play_simple_movie_example.c -o bin/movieplayer

smash:
	acom -std=c99 -Ilib labs/smash.c lib/xwd_tools.c -o bin/smash

all: lab1 lab2 movieplayer

clean:
	rm -f *.xwd
	rm -rf bin/*
