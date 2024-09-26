﻿#pragma once

#ifndef Debug_h
#define Debug_h

#include <iostream>

class Debug
{
public:
	void startUp()
	{
        std::cout << R"(
                                                        _...--.
                                        _____......----'     .'
                                  _..-''                   .'
                                .'                       ./
                        _.--._.'                       .' |
                     .-'                           .-.'  /
                   .'   _.-.                     .  \   '
                 .'  .'   .'    _    .-.        / `./  :
               .'  .'   .'  .--' `.  |  \  |`. |     .'
            _.'  .'   .' `.'       `-'   \ / |.'   .'
         _.'  .-'   .'     `-.            `      .'
       .'   .'    .'          `-.._ _ _ _ .-.    :
      /    /o _.-'               .--'   .'   \   |
    .'-.__..-'                  /..    .`    / .'
  .'   . '                       /.'/.'     /  |
 `---'                                   _.'   '
                                       /.'    .'
                                        /.'/.'
    )" << std::endl;

        std::cout << R"(
  _______  _______ .__   __.   _______  __  .__   __.  _______    
 /  _____||   ____||  \ |  |  /  _____||  | |  \ |  | |   ____|   
|  |  __  |  |__   |   \|  | |  |  __  |  | |   \|  | |  |__      
|  | |_ | |   __|  |  . `  | |  | |_ | |  | |  . `  | |   __|     
|  |__| | |  |____ |  |\   | |  |__| | |  | |  |\   | |  |____    
 \______| |_______||__| \__|  \______| |__| |__| \__| |_______|  
    )" << std::endl;

	}
	
	void log(const char* output) 
	{
        std::cout << prefixLog << output << std::endl;
	}

	void warning(const char* output)
	{
        std::cout << prefixWarning << output << std::endl;
	}

private:
	std::string prefixLog = "O : ";
	std::string prefixWarning = "! : ";
};

#endif // debug_h