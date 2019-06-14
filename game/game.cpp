#include "game.h"

void show_banner() {
	std::string introBanner = R"EOF(        _
       (_)
       |=|
       |=|
   /|__|_|__|\
  (    ( )    )                Welcome to Emberstorm RPG!
   \|\/\"/\/|/              >>>>>-------------------------->
     |  Y  |
     |  |  |
     |  |  |
    _|  |  |
 __/ |  |  |\
/  \ |  |  |  \
   __|  |  |   |
/\/  |  |  |   |\
 <   +\ |  |\ />  \
  >   + \  | LJ    |
        + \|+  \  < \
  (O)      +    |    )
   |             \  /\ 
 ( | )   (o)      \/  )
_\\|//__( | )______)_/ 
        \\|//

)EOF";
	std::cout << introBanner;
}

void update() {
	srand(time(NULL));
}
