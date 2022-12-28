
(THIS IS FOR BOTH *SDL2*  AND *SDL2_IMAGE*)

Open sdl1.sln file

In properties
->in VC++ directories
    ->set Include directories
    ->set Library directories

->In C/C++ -> Genral
    ->set Additional Include directories

->In Linker -> Genral
    ->set Additional Library directories

->In Linker -> Input 
    ->in Additional Dependencies type SDL2.lib
                                      SDL2main.lib
                                      SDL2_image.lib

Move with WASD.
