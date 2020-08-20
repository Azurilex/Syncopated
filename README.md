# Syncopated
## Preface
Syncopated was made to showcase all the bypasses, methods, and exploits ever used in the 2016-2020 era of Roblox exploiting. Syncopated, contains 3 different retcheck bypasses, and 2 different methods of obtaining Lua State. The user running Syncopated, literally gets to choose how the exploit functions. You can choose how you want to get Lua State, and how you want to get retcheck. Please keepin mind, this is a *demo*, it will never be a full fledged script executor. Right now, all it will do is print out "done lol" to Roblox's console (print("done lol")) via the Lua C API. I will be working on this in my spare time to bring it more features, more exploits, more bypasses, etc. So stay tuned

## Information
### Memory
Syncopated stores the rLua C API inside of objects, this gives a noticable decrease in memory usage.
### Bypasses
#### Brandon's Retcheck Bypass
Written by Brandon/Chirality. Works extremely similarily to Eternal's bypass, hell, Eternal's bypass was completely based off of this one. This bypass has been found to be the most efficient of the two though, however, it isn't as light-weight as Eternal's.
#### Eternal's Retcheck Bypass
Based off of Brandon's bypass, this bypass was released in 2017 by Eternal. It works by copying the function to a seperate, un-hashed, portion of memory then proceeds to alter the flow of the check, preventing a shutdown. (https://github.com/EternalV3/Retcheck)
#### JBRR Retcheck Bypass
This method was widly used in 2016 to bypass retcheck. When an rLua C function is run, before the actual execution of the function, we switch the check's conditional jump, to a jump that goes over the flag. Then the function runs, and switch it back immediately after to avoid being flagged by ROBLOX's memory check. In the end, this method bypasses ROBLOX's memory check with simplicity, and ease - however, it is not as efficient as other methods.

## Contributing
As most of you know, I love Github. So feel free to fork the repository and make pull requests as you please, I'm totally open to new ideas.

## Credits
@Azurilex - Developing Syncopated, JBRR Retcheck bypass\
@EternalV3 - Eternal's Retcheck Bypass\
Brandon - Brandon's Retcheck Bypass\
@sloppey - Temp-hook Lua State method
