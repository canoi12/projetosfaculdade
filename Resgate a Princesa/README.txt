Para compilar:

g++ Bloco.cpp BolaDeFogo.cpp GameControl.cpp Player.cpp Recursos.cpp "Resgate a princesa.cpp" -o main 
-lallegro -lallegro_image -lallegro_primitives -lallegro_audio -lallegro_ttf -lallegro_font -lalgif -lallegro_acodec -lallegro_dialog

É necessário linkar a biblioteca algif(algif.sourceforge.net):

HOW TO USE

The first, and hardest step, is to compile it. This may seem very simple:

gcc -c *.c
ar -rcs libalgif.a *.o

Or simply compile the .c files along with your project.

But in practice, it is much harder. You may prefer to use a makefile, in which case you can try the provided one, it was tested with a recent mingw and linux distribution.

The makefile also has an install target, so if you type "make install", it will copy the libalgif.a to /usr/local/lib or $MINGDIR/lib and algif.h to /usr/local/include or $MINGDIR/include.

And last, put include <algif.h> at the top of the source files where you want to use functions out of it, and link your program against it. With gcc, just add -lalgif as option.