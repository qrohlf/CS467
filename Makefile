lab1:
	acom -std=c99 -Ilib labs/lab1.c lib/D3d_matrix_student.c -o bin/lab1
lab2:
	acom -std=c99 -Ilib labs/lab2.c lib/D3d_matrix_student.c lib/vectors.c lib/light_model_student.c -o bin/lab2